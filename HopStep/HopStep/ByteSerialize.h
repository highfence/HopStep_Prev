#pragma once
#include <vector>
#include <memory>
#include <type_traits>
#include <iostream>
#include <iomanip>

namespace HopStep
{
	// Maybe switching with std::byte...?
	using byte = char;

	class ByteSerializer
	{
	public :

		template <class T>
		static std::vector<byte> SerializeToByte(const T& obj);
			
		template <class T>
		static T& DeserializeFromByte(const std::vector<byte>& bytes, T& object);

	};

	template<class T>
	inline std::vector<byte> ByteSerializer::SerializeToByte(const T & obj)
	{
		std::vector<byte> bytes;

		const byte* begin = reinterpret_cast<const byte*>(std::addressof(obj));
		const byte* end = begin + sizeof(T);
		std::copy(begin, end, std::begin(bytes));

		return bytes;
	}

	template<class T>
	inline T & ByteSerializer::DeserializeFromByte(const std::vector<byte>& bytes, T & object)
	{
		byte* begin_object = reinterpret_cast<byte*>(std::addressof(object));
		std::copy(std::begin(bytes), std::end(bytes), begin_object);

		return object;
	}
}
