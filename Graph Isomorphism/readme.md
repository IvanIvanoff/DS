# Изоморфизъм на дървета

* Използван алгоритъм: *Algorithm by Aho, Hopcroft and Ullman*
> Source: http://logic.pdmi.ras.ru/~smal/files/smal_jass08_slides.pdf


How to use:
```C++
int main()
{
	std::string t1, t2;
	std::getline(std::cin, t1);
	std::getline(std::cin, t2);

	if(are_isomorphic(t1,t1)){
		std::cout<<"The trees are isomorphic!\n";
	}else{
		std::cout<<"The trees are not isomorphic or the input is incorrect!\n";
	}
	return 0;
}
```