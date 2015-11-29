#pragma once


enum class NeuronTypes : int
{
	None,			// 없음
	Normal,			// 일반뉴런
	Positive,		// P호르몬뉴런
	Negative,		// N호르몬뉴런
};


enum class AxonTypes : int
{
	None,			// 없음
	Input,			// 뉴런의 입력측
	Output,			// 뉴런의 출력측
};

