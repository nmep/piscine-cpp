# include "PmergeMe.hpp"

unsigned long long	ft_atoull(std::string & str)
{
	int	i = 0;
	unsigned long long res = 0;
	if (str.size() == 0)
		throw std::invalid_argument("Empty argument");
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			throw std::invalid_argument("Only positive integer");
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((res > ULLONG_MAX / 10)
			|| (res == ULLONG_MAX / 10 && (str[i] - 48) >  static_cast<int>(ULLONG_MAX % 10)))
			throw std::out_of_range("Overflow");
		res = res * 10 + (str[i] - 48);
		i++;
	}
	if (str[i] != '\0')
		throw std::invalid_argument(std::string(1, str[i]) + " invalid argument");
	return res;
}




// ---------------------------------------------//


//					DEQUE


// ---------------------------------------------//




bool	ft_merge_sort_max_element_deque(std::deque<unsigned long long> *d, d_it start, d_it end,\
	 std::deque<unsigned long long> *max_elements)
{
	int range = std::distance(start, end);

	if (range > 2)
	{
		d_it median = start + range / 2;
		if (ft_merge_sort_max_element_deque(d, start, median, max_elements))
			return true;
		// std::cout << "autre partie" << std::endl;
		if (ft_merge_sort_max_element_deque(d, median, end, max_elements))
			return true;
	}

	if (range == 2)
	{
		if (*start > *(end))
		{
			ft_binary_search_insertion_elements_deque(max_elements, *start, static_cast<int>(max_elements->size() / 2));
			d->erase(start);
			return true;
		}
		else
		{
			ft_binary_search_insertion_elements_deque(max_elements, *(end), static_cast<int>(max_elements->size() / 2));
			d->erase(end);
			return true;
		}
	}
	return false;
}

bool	ft_binary_search_insertion_elements_deque(std::deque<unsigned long long> *me, unsigned long long val, int median)
{
	// creer une partie left et right de me
	std::deque<unsigned long long> left;
	std::deque<unsigned long long> right;

	if (me->empty())
	{
		me->push_back(val);
		return true;
	}

	if (me->size() > 1)
	{
		left.insert(left.begin(), me->begin(), me->begin() + median);

		right.insert(right.begin(), me->begin() + median, me->end());

	// repeter jusqua ce que la taille soit de 1
		// comparer a la valeur median si elle est supp ou inf

		// si elle est supp refaire avec la median right
		if (std::distance(me->begin(), me->end()) == median)
			median--;
		if (val > (*me)[median])
		{
			// si la fonction a trouver et a inserer la valeur clear me et merge left et right puis return
			if (ft_binary_search_insertion_elements_deque(&right, val, right.size() * 0.5))
			{
				me->clear();
				me->insert(me->begin(), left.begin(), left.end());
				me->insert(me->end(), right.begin(), right.end());
				return true;
			}
			// le return permet de ne pas continuer si on a trouver ou insert la valeur
			// sinon elle sera reinsserre ailleur
		}
		// sinon avec la median left
		else
		{
			if (ft_binary_search_insertion_elements_deque(&left, val, left.size() * 0.5))
			{
				me->clear();
				me->insert(me->begin(), left.begin(), left.end());
				me->insert(me->end(), right.begin(), right.end());
				return true;
			}
			ft_binary_search_insertion_elements_deque(&left, val, left.size() * 0.5);
		}
	}
	if (val > *(me->begin()))
	{
		me->insert(me->begin() + 1, val);
		return true;
	}
	else
	{
		me->insert(me->begin(), val);
		return true;
	}
	return false;
}

// insert un a un les elements de d dans max_elements par dichotomie
void	ft_insert_in_max_elements_deque(std::deque<unsigned long long> *d, std::deque<unsigned long long> *max_elements)
{
	// prendre le premier element de d et l'envoyer dans bsi
	if (d->size() != 0)
	{
		ft_binary_search_insertion_elements_deque(max_elements, *(d->begin()), max_elements->size() / 2);
		// supprimer le premier element de d
		d->erase(d->begin());
		// refaire jusqu'a que d soit vide
		ft_insert_in_max_elements_deque(d, max_elements);
	}

	// une fois que d est vide copier me dans d
	else
	{
		d->clear();
		d->insert(d->begin(), max_elements->begin(), max_elements->end());
		max_elements->clear();
	}
}

void	ft_FordJohnsonDeque(std::deque<unsigned long long> *d)
{
	std::deque<unsigned long long> max_elements;

	// etape 1
	ft_merge_sort_max_element_deque(d, d->begin(), d->end(), &max_elements);
	// etape 2
	ft_insert_in_max_elements_deque(d, &max_elements);

}



// ---------------------------------------------//


//					vector


// ---------------------------------------------//





bool	ft_merge_sort_max_element_vector(std::vector<unsigned long long> *v, v_it start, v_it end,\
	 std::vector<unsigned long long> *max_elements)
{
	int range = std::distance(start, end);

	if (range > 2)
	{
		v_it median = start + range / 2;
		if (ft_merge_sort_max_element_vector(v, start, median, max_elements))
			return true;
		// std::cout << "autre partie" << std::endl;
		if (ft_merge_sort_max_element_vector(v, median, end, max_elements))
			return true;
	}

	if (range == 2)
	{
		if (*start > *(end))
		{
			ft_binary_search_insertion_elements_vector(max_elements, *start, static_cast<int>(max_elements->size() / 2));
			v->erase(start);
			return true;
		}
		else
		{
			ft_binary_search_insertion_elements_vector(max_elements, *(end), static_cast<int>(max_elements->size() / 2));
			v->erase(end);
			return true;
		}
	}
	return false;
}

bool	ft_binary_search_insertion_elements_vector(std::vector<unsigned long long> *me, unsigned long long val, int median)
{
	// creer une partie left et right de me
	std::vector<unsigned long long> left;
	std::vector<unsigned long long> right;

	if (me->empty())
	{
		me->push_back(val);
		return true;
	}

	if (me->size() > 1)
	{
		left.insert(left.begin(), me->begin(), me->begin() + median);

		right.insert(right.begin(), me->begin() + median, me->end());

	// repeter jusqua ce que la taille soit de 1
		// comparer a la valeur median si elle est supp ou inf

		// si elle est supp refaire avec la median right
		if (std::distance(me->begin(), me->end()) == median)
			median--;
		if (val > (*me)[median])
		{
			// si la fonction a trouver et a inserer la valeur clear me et merge left et right puis return
			if (ft_binary_search_insertion_elements_vector(&right, val, right.size() * 0.5))
			{
				me->clear();
				me->insert(me->begin(), left.begin(), left.end());
				me->insert(me->end(), right.begin(), right.end());
				return true;
			}
			// le return permet de ne pas continuer si on a trouver ou insert la valeur
			// sinon elle sera reinsserre ailleur
		}
		// sinon avec la median left
		else
		{
			if (ft_binary_search_insertion_elements_vector(&left, val, left.size() * 0.5))
			{
				me->clear();
				me->insert(me->begin(), left.begin(), left.end());
				me->insert(me->end(), right.begin(), right.end());
				return true;
			}
			ft_binary_search_insertion_elements_vector(&left, val, left.size() * 0.5);
		}
	}
	if (val > *(me->begin()))
	{
		me->insert(me->begin() + 1, val);
		return true;
	}
	else
	{
		me->insert(me->begin(), val);
		return true;
	}
	return false;
}


// insert un a un les elements de d dans max_elements par dichotomie
void	ft_insert_in_max_elements_vector(std::vector<unsigned long long> *v, std::vector<unsigned long long> *max_elements)
{
	// prendre le premier element de v et l'envoyer dans bsi
	if (v->size() != 0)
	{
		ft_binary_search_insertion_elements_vector(max_elements, *(v->begin()), max_elements->size() / 2);
		// supprimer le premier element de v
		v->erase(v->begin());
		// refaire jusqu'a que v soit vide
		ft_insert_in_max_elements_vector(v, max_elements);
	}
	else
	{
		v->clear();
		v->insert(v->begin(), max_elements->begin(), max_elements->end());
		max_elements->clear();
	}
}

void	ft_FordJohnsonvector(std::vector<unsigned long long> *v)
{
	std::vector<unsigned long long> max_elements;

	// etape 1
	ft_merge_sort_max_element_vector(v, v->begin(), v->end(), &max_elements);

	// etape 2
	ft_insert_in_max_elements_vector(v, &max_elements);

}