/* Суть игры:
Попросите пользователя ввести 2 числа: 
первое — стартовое число, которое нужно возвести в квадрат, 
второе — количество чисел, которые нужно возвести в квадрат.
Сгенерируйте случайное целое число от 2 до 4 
и возведите в квадрат указанное пользователем количество чисел, начиная со стартового.
Умножьте каждое возведённое в квадрат число на сгенерированное ранее число (от 2 до 4).
Пользователь должен вычислить, какие числа были сгенерированы — он указывает свои предположения.
Программа проверяет, угадал ли пользователь число, и, если угадал, удаляет угаданное число из списка.
Если пользователь не угадал число, то игра заканчивается, и программа выводит число, 
которое было ближе всего к окончательному предположению пользователя, 
но только если последнее предположение не отличалось больше чем на 4 единицы от числа из списка.*/

#include <iostream>
#include <string>
#include <ctime>      // для randomize
#include <cmath>      // abs()
#include <vector>

using std::cin; using std::cout;

// получает натуральное число от пользователя
unsigned get_number(const std::string& text_for_user)
{
	cout << text_for_user;
	int answer;
	cin >> answer;
	while (cin.fail() || (answer < 0))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Нужно ввести натуральное число, повторите ввод: ";
		cin >> answer;
	}
	return static_cast<unsigned>(answer);
}

// возвращает число массива, наиболее близкое к заданному и его разницу с числом от пользователя
unsigned find_the_closest_number(const std::vector<unsigned>& numbers_to_guess, const unsigned users_try, unsigned& distance)
{
	unsigned the_closest_number{ numbers_to_guess[0] };
	distance = std::abs(static_cast<int>(the_closest_number) - static_cast<int>(users_try));
	for (const auto each_number : numbers_to_guess)
		if (std::abs(static_cast<int>(each_number) - static_cast<int>(users_try)) < distance)
		{
			the_closest_number = each_number;
			distance = std::abs(static_cast<int>(each_number) - static_cast<int>(users_try));
		}
	return the_closest_number;
}

int main()
{
	setlocale(LC_CTYPE, "rus");                   // подключаем кириллицу для вывода сообщений пользователю
	srand(static_cast<unsigned>(time(0)));        // аналог randomize

	const unsigned start_number{ get_number("Введите стартовое число, которое нужно возвести в квадрат: ") };
	const unsigned n_number{ get_number("Введите количество чисел, которые нужно возвести в квадрат: ") };
	const unsigned random_number_from_2_to_4{ static_cast<unsigned>(rand()) % 3 + 2 };

	// создаём числа для угадывания
	std::vector<unsigned> numbers_to_guess{};
	for (unsigned i = 0; i < n_number; ++i)
		numbers_to_guess.push_back((start_number + i) * (start_number + i) * random_number_from_2_to_4);
	cout << "Сгенерировано " << n_number << " чисел/число/числа. Попробуйте угадать числа после умножения их квадратов на " << random_number_from_2_to_4 << "!\n";

	while (true)                                  // цикл угадывания очередного числа
	{ 
		unsigned user_tryes_to_guess{ get_number("Ваше предположение: ") };
		// лямбда, которая возвращает true, если такое число есть в списке
		auto found{ [&numbers_to_guess](const auto number_to_find)
		            {return std::find(numbers_to_guess.begin(), numbers_to_guess.end(), number_to_find); } };
		if (found(user_tryes_to_guess) < numbers_to_guess.end())
		{
			numbers_to_guess.erase(found(user_tryes_to_guess));
			if (numbers_to_guess.empty())
			{
				cout << "Очень здорово! Вы угадали все числа! \n";
				break;
			}
			cout << "Верно! Вы угадали. Осталось отгадать " << numbers_to_guess.size() << " чисел/число/числа\n";
		}
		else
		{
			cout << "К сожалению, Вы не угадали число. ";
			unsigned distance{ 1 };          // разница между названным числом и наиболее близким к нему из массива
			unsigned the_closest_number{ find_the_closest_number(numbers_to_guess, user_tryes_to_guess, distance)};
			if (distance < 5)
				cout << "Было бы лучше, если бы Вы назвали " << the_closest_number << "...\n";
			break;
		}
	}
	cout << "Игра окончена.\n";
	return 0;
}