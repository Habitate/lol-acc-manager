#include "menu.h"
#include "color.h"

using namespace std;

Menu::Menu() : selection(0), entries(){}

void Menu::emplace_back(const string& val){
	entries.emplace_back(val);
}

unsigned int Menu::get_selection() const noexcept{
	return selection;
}

ostream& operator<<(ostream& stream, const Menu& menu){
	for(vector<string>::size_type i = 0, last = menu.entries.size(); i < last; ++i){
		if(i == menu.selection){
    		cout << i + 1 << ". " << C(15) << "> " << menu.entries[i] << '\n' << C();
    	}
    	else{
			cout << i + 1 << ".   " << menu.entries[i] << '\n';
		}
	}

	return stream;
}

void Menu::mv_up() noexcept{
	if(selection == 0){
		selection = entries.size() - 1;
	}
	else{
		--selection;
	}
}
void Menu::mv_down() noexcept{
	if(selection == entries.size() - 1){
		selection = 0;
	}
	else{
		++selection;
	}
}