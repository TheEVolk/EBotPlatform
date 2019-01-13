/*
    Copyright Elektro-Volk 2018
    EMail: elektro-volk@yandex.ru
    VK: https://vk.com/ebotp

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
//#define BUILDING_LIBCURL
#include "ENet.hpp"
#include "EConsole.hpp"
#include <cpprest/http_client.h>

using namespace web;
using namespace web::http::client;

ENet *e_net;

ENet::ENet()
{
}

string ENet::urlEncode(string str)
{
	char* esc_text = curl_easy_escape(NULL, str.c_str(), str.length());
	if (!esc_text) throw std::runtime_error("Can not convert string to URL");
	string result = esc_text;
	curl_free(esc_text);
	return result;
}

string ENet::urlDecode(string str)
{
	char* esc_text = curl_easy_unescape(NULL, str.c_str(), str.length(), NULL);
	if (!esc_text) throw std::runtime_error("Can not convert URL to string");
	string result = esc_text;
	curl_free(esc_text);
	return result;
}

std::string ENet::sendGet(std::string url)
{
	http_client client(utility::conversions::to_string_t(url));
	http::http_request request(http::methods::GET);

	auto re = client.request(request).then([](http::http_response response)
	{
		if (response.status_code() == http::status_codes::OK)
		{
			//response.headers().set_content_type(U("text/plain"));
			return response.extract_utf8string(true).get();
		}
	});
	re.wait();
	return re.get();
}

string ENet::sendPost(string url, std::map<string, string> params)
{
    string paramline;
	for (auto iter = params.begin(); iter != params.end(); iter++) {
		paramline.append(iter->first + "=" + urlEncode(iter->second) + "&");
	}

    return this->sendPost(url, paramline);
}

string ENet::sendPost(string url, string postdata)
{
	http_client client(utility::conversions::to_string_t(url));
	http::http_request request(http::methods::POST);
	request.set_body(postdata, "application/x-www-form-urlencoded");

	auto re = client.request(request).then([](http::http_response response)
	{
		if (response.status_code() == http::status_codes::OK)
		{
			//response.headers().set_content_type(U("text/plain"));
			return response.extract_utf8string(true).get();
		}
	});

	re.wait();

	return re.get();
}

ENet::~ENet()
{

}
