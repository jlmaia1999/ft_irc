#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include <iostream>
#include <vector>
#include <set>
#include "../server.hpp"

class Channel
{
	private:
		std::string _name;
		std::string _topic;
		std::set<Client> _members;
		std::set<Client> _operators;
	public:
		Channel();
		~Channel();
		Channel(const std::string &name);
		const std::string &getName() const;
		void addMember(Client client_id);
		void removeMember(Client client_id);
		bool hasMember(Client client_id) const;
		bool empty() const;
};

#endif