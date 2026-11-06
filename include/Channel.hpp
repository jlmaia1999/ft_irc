#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include <iostream>
#include <vector>
#include <set>

class Channel
{
	private:
		std::string _name;
		std::string _topic;
		std::set<int> _members; //replace <int> with Client object
		std::set<int> _operators; //replace <int> with Client object
	public:
		Channel(const std::string &name);
		const std::string &getName() const;
		void addMember(int client_id); //replace int with Client object
		void removeMember(int client_id); //replace int with Client object
		bool hasMember(int client_id) const; //replace int with Client object
		bool empty() const;
};

#endif