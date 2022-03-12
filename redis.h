#pragma once
#ifndef _REDIS_H_
#define _REDIS_H_

#include <iostream>
#include <string.h>
#include <string>
#include <stdio.h>

#include <hiredis/hiredis.h>

class Redis {
private:
	redisContext* connect;
	redisReply* reply;
public:
	Redis(){}
	~Redis() {
		this->connect = NULL;
		this->reply = NULL;
	};

	bool connect(std::string ip, int port) {
		this->connect = redisConnect(ip.c_str(), port);
		if (this->connect != NULL && this->connect->err) {
			return false;
		}
		return true;
	};

	bool isConnect() {
		return this->connect != NULL && !this->connect->err;
	};

	std::string get(std::string key) {
		this->reply = (redisReply*)redisCommand(this->connect, "get '%s'", key.c_str());
		std::string str = this->reply->str;
		freeReplyObject(this->reply);
		return str;
	};

	void* set(std::string key, std::string value) {
		redisCommand(this->connect, "set '%s' '%s'", key.c_str(), value.c_str());
	};
};

#endif