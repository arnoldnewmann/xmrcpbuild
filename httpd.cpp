#ifndef CONF_NO_HTTPD

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>

#include "msgstruct.h"
#include "httpd.h"
#include "console.h"
#include "executor.h"
#include "jconf.h"

#include "webdesign.h"

#include <microhttpd.h>
#ifdef _WIN32
#define strcasecmp _stricmp
#endif // _WIN32

httpd* httpd::oInst = nullptr;

httpd::httpd()
{

}

int httpd::req_handler(void * cls,
	        MHD_Connection* connection,
	        const char* url,
	        const char* method,
	        const char* version,
	        const char* upload_data,
	        size_t* upload_data_size,
	        void ** ptr)
{
	struct MHD_Response * rsp;

	if (strcmp(method, "GET") != 0)
		return MHD_NO;

	*ptr = nullptr;

	std::string str;
	if(strcasecmp(url, "/style.css") == 0)
	{
		const char* req_etag = MHD_lookup_connection_value(connection, MHD_HEADER_KIND, "If-None-Match");

		if(req_etag != NULL && strcmp(req_etag, sHtmlCssEtag) == 0)
		{ //Cache hit
			rsp = MHD_create_response_from_buffer(0, nullptr, MHD_RESPMEM_PERSISTENT);

			int ret = MHD_queue_response(connection, MHD_HTTP_NOT_MODIFIED, rsp);
			MHD_destroy_response(rsp);
			return ret;
		}

		rsp = MHD_create_response_from_buffer(sHtmlCssSize, (void*)sHtmlCssFile, MHD_RESPMEM_PERSISTENT);
		MHD_add_response_header(rsp, "ETag", sHtmlCssEtag);
		MHD_add_response_header(rsp, "Content-Type", "text/css; charset=utf-8");
	}
	else if(strcasecmp(url, "/api.json") == 0)
	{
		executor::inst()->get_http_report(EV_HTML_JSON, str);

		rsp = MHD_create_response_from_buffer(str.size(), (void*)str.c_str(), MHD_RESPMEM_MUST_COPY);
		MHD_add_response_header(rsp, "Content-Type", "application/json; charset=utf-8");
	}
	else if(strcasecmp(url, "/h") == 0 || strcasecmp(url, "/hashrate") == 0)
	{
		executor::inst()->get_http_report(EV_HTML_HASHRATE, str);

		rsp = MHD_create_response_from_buffer(str.size(), (void*)str.c_str(), MHD_RESPMEM_MUST_COPY);
		MHD_add_response_header(rsp, "Content-Type", "text/html; charset=utf-8");
	}
	else if(strcasecmp(url, "/c") == 0 || strcasecmp(url, "/connection") == 0)
	{
		executor::inst()->get_http_report(EV_HTML_CONNSTAT, str);

		rsp = MHD_create_response_from_buffer(str.size(), (void*)str.c_str(), MHD_RESPMEM_MUST_COPY);
		MHD_add_response_header(rsp, "Content-Type", "text/html; charset=utf-8");
	}
	else if(strcasecmp(url, "/r") == 0 || strcasecmp(url, "/results") == 0)
	{
		executor::inst()->get_http_report(EV_HTML_RESULTS, str);

		rsp = MHD_create_response_from_buffer(str.size(), (void*)str.c_str(), MHD_RESPMEM_MUST_COPY);
		MHD_add_response_header(rsp, "Content-Type", "text/html; charset=utf-8");
	}
	else
	{
		//Do a 302 redirect to /h
		char loc_path[256];
		const char* host_val = MHD_lookup_connection_value(connection, MHD_HEADER_KIND, "Host");

		if(host_val != nullptr)
			snprintf(loc_path, sizeof(loc_path), "http://%s/h", host_val);
		else
			snprintf(loc_path, sizeof(loc_path), "/h");

		rsp = MHD_create_response_from_buffer(0, nullptr, MHD_RESPMEM_PERSISTENT);
		int ret = MHD_queue_response(connection, MHD_HTTP_TEMPORARY_REDIRECT, rsp);
		MHD_add_response_header(rsp, "Location", loc_path);
		MHD_destroy_response(rsp);
		return ret;
	}

	int ret = MHD_queue_response(connection, MHD_HTTP_OK, rsp);
	MHD_destroy_response(rsp);
	return ret;
}

bool httpd::start_daemon()
{
	d = MHD_start_daemon(MHD_USE_THREAD_PER_CONNECTION,
		jconf::inst()->GetHttpdPort(), NULL, NULL,
		&httpd::req_handler,
		NULL, MHD_OPTION_END);

	if(d == nullptr)
	{
		printer::inst()->print_str("HTTP Daemon failed to start.");
		return false;
	}

	return true;
}

#endif

