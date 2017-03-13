#ifndef ADDRESS_HPP_
# define ADDRESS_HPP_

# include <Winsock2.h>
# include <string>
# include "API_Socket_Udp.hpp"

namespace API_Socket_Udp_Windows
{
    class Address : public API_Socket_Udp::IAddress
    {
    private:
	struct sockaddr		    _address;
	int			    _addrLen;
	std::string		    _str;

	void			    updateString();

    public:
	Address(const struct sockaddr &val, int len);
	virtual ~Address();

	virtual const std::string   &toString() const;
	virtual int		    getPort() const;

	const SOCKADDR		    *getSockAddr() const;
	int			    getAddrLen() const;

	void			    update(const struct sockaddr &val, int len);
    };
}

#endif // !ADDRESS_HPP_