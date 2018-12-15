#pragma once
#include <array>
#include <memory>
#include <type_traits>
#include <iostream>
#include <iomanip>

namespace HopStep
{
	// Maybe switching with std::byte...?
	using byte = unsigned char;

	class ByteSerializer
	{
	public :

		template <class T>
		static std::array<byte, sizeof(T)> SerializeToByte(const T& obj);
			
		template <class T>
		static T& DeserializeFromByte(const std::array<byte, sizeof(T)>& bytes, T& object);

	};

	template<class T>
	inline std::array<byte, sizeof(T)> ByteSerializer::SerializeToByte(const T & obj)
	{
		std::array< byte, sizeof(T) > bytes;

		const byte* begin = reinterpret_cast<const byte*>(std::addressof(obj));
		const byte* end = begin + sizeof(T);
		std::copy(begin, end, std::begin(bytes));

		return bytes;
	}

	template<class T>
	inline T & ByteSerializer::DeserializeFromByte(const std::array<byte, sizeof(T)>& bytes, T & object)
	{
		// http://en.cppreference.com/w/cpp/types/is_trivially_copyable
		static_assert(std::is_trivially_copyable<T>::value, "not a TriviallyCopyable type");

		byte* begin_object = reinterpret_cast<byte*>(std::addressof(object));
		std::copy(std::begin(bytes), std::end(bytes), begin_object);

		return object;
	}
}
