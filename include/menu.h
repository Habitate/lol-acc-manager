#pragma once

#include <vector>
#include <iostream>

class Menu{
	public:
		Menu();

		template<typename It, typename Func>
		Menu(It begin, It end, Func func) : selection(0), entries(){
			for(; begin != end; ++begin){
				entries.emplace_back(func(*begin));
			}
		}

		void emplace_back(const std::string& val);

		unsigned int get_selection() const noexcept;

		friend std::ostream& operator<<(std::ostream& stream, const Menu& menu);

		void mv_up() noexcept;
		void mv_down() noexcept;

	private:
		unsigned int selection;

		std::vector<std::string> entries;
};