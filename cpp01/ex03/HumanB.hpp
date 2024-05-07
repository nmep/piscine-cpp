#ifndef HUMAN_B
# define HUMAN_B

# include "Weapon.hpp"

class HumanB
{
	private:
		Weapon*		_Weapon;
		std::string	_name;
	public:
		HumanB(std::string name);
		~HumanB(void);

		void	setWeapon(Weapon &rand_Weapon);
		void	attack(void) const;
};

# endif