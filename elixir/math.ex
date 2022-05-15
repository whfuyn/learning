defmodule Math do
	def zero?(0) do
		true
	end
	def zero?(x) when is_integer(x) do
		false
	end

	def sum(a, b) do
		a + b
	end
	
	def sum_list(list, acc \\ 0)
	def sum_list([head | tail], acc), do: sum_list(tail, head + acc)
	def sum_list([], acc), do: acc

	def double_each([]), do: []
	def double_each([head | tail]), do: [head * 2 | double_each(tail)]
end

