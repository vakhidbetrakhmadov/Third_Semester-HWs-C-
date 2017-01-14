/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW07_141044086_Vakhid_Betrakhmadov                                       */
/*                                                                          */
/* MyExeption.h                                                             */
/* ---------                                                                */
/* Created on 26/12/2016 by Vakhid_Betrakhmadov                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/
#ifndef MY_EXEPTION_H
#define MY_EXEPTION_H

#include <exception>
#include <string>

using std::exception;
using std::string;

namespace MansBT
{
	class MyExeption: public exception
	{
	public:
 
		MyExeption()throw()
		 	:message(string())
		{
			//empty body
		}

		MyExeption(const string& the_message)throw()
			:message(the_message)
		{
			//empty body
		}

		virtual ~MyExeption()throw()
		{
			//empty body
		}

		virtual const char* what()const throw()
		{
			return message.c_str();
		}

	private:
		string	message;
	};
}

#endif