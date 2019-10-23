#include "vir.h"

virtIO::virtIO_t()
{
	m_file=NULL;
	m_name=" ";
	m_mode=" ";
	m_position=0;
	m_status=ok_e;
}

virtIO_t::virtIO_t(const string name, const string mode)
{
	m_file=NULL;
	m_name=name;
	m_mode=mode;
	m_position=0;
	m_status=ok_e;
}

bool virtIO_t::openFile(const string name,const string mode)
{ 
	m_file= fopen(name.c_str(),mode.c_str()); 
	if(m_file)
	{
		m_status=ok_e;
		return 1;
	}
	m_status=cant_open_file_e;
	return 0;
}

void virtIO_t::closeFile()
{ 
	fclose(m_file); 
}

const char* virtIO_t::getBath() const
{
	char* actualpath=new char[PATH_MAX+1];
	char *ptr;
	const char *c = m_name.c_str();
	ptr=realpath(c,actualpath);
	if(ptr)
		return actualpath;
	delete actualpath;
	return NULL;
}

const size_t virtIO_t::getLength() const
{
	size_t size=0;
	if(m_file)
	{
		fseek(m_file, 0, SEEK_END);
		size = ftell(m_file);
		fseek(m_file,m_position, SEEK_SET);
	}
	return size;
}

bool virtIO_t::setPosition(size_t pos)
{
	if((m_file)&&(pos<getLength()))
	{
		m_position=pos;
		fseek(m_file,m_position, SEEK_SET);
		return 1;
	}
	return 0;
}

virtIO_t::~virtIO_t() {}