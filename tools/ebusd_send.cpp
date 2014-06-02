/*
 * Copyright (C) Roland Jax 2012-2014 <roland.jax@liwest.at>
 *
 * This file is part of ebusd.
 *
 * ebusd is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ebusd is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ebusd. If not, see http://www.gnu.org/licenses/.
 */

#include "appl.h"
#include "tcpsocket.h"
#include <iostream>
#include <cstdlib>

Appl& A = Appl::Instance();

void define_args()
{
	A.addItem("p_server", Appl::Param("localhost"), "s", "server",
		  "servername or IP (localhost)",
		  Appl::type_string, Appl::opt_mandatory);

	A.addItem("p_port", Appl::Param(8888), "p", "port",
		  "\tport (8888)",
		  Appl::type_int, Appl::opt_mandatory);

	A.addItem("p_help", Appl::Param(false), "h", "help",
		  "print this message",
		  Appl::type_bool, Appl::opt_none);
}

int main(int argc, char* argv[])
{
	// define Arguments and Application variables
	define_args();

	// parse Arguments
	if (A.parseArgs(argc, argv) == false) {
		A.printArgs();
		exit(EXIT_FAILURE);
	}

	// print Help
	if (A.getParam<bool>("p_help") == true) {
		A.printArgs();
		exit(EXIT_SUCCESS);
	}

	TCPClient* client = new TCPClient();
	TCPSocket* socket = client->connect(A.getParam<const char*>("p_server"), A.getParam<int>("p_port"));
	//~ TCPSocket* socket = client->connect(A.getParam<const char*>("p_server"), A.getParam<int>("p_port"));

	delete socket;
	delete client;

	return 0;

}

