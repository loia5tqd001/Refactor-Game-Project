#pragma once

class Data
{
	std::unordered_map<std::string, const std::any> data;

public:
	template<typename T>
	void Add(const std::string& property, T value)
	{
		assert(data.count(property) == 0);
		data.emplace(property, value);
	}

	template<typename T>
	inline auto Get(const std::string& property) const
	{
		assert(data.count(property) == 1);
		return std::any_cast<T>( data.at(property) );
	}

	inline auto Count(const std::string& property) const
	{
		return data.count(property);
	}
};

/*  Sample use of 'Data':
	Data data;
	data.Add("water-velocity", 16.9f);
	data.Add("damage", 420);

	cout << data.Get<float>("water-velocity") << endl;
	cout << data.Get<int>("damage") << endl;
*/
