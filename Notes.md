# C++ Notes

## set_union 
`set_union` is useful to find an union of two sorted vectors, where `result` is also sorted:

```
set_union(first.begin(), first.end(), 
          second.begin(), second.end(), 
          result.begin());
```

## back_inserter
The `push_back` is called whenever the iterator is assigned to. It is really useful using it with other STL algorithms.

## optional
`std::optional` contains a value or not.  It can be used with `if`:

```
if (auto value = get_optional_value()) {
  std::cout << *value;
}
```

- `nullopt` used for the absent value.
- `value_or` is useful for getting the value or the specified value.

## list
- `list::splice` concatenates two lists in `O(1)` time, without any copying of data.
- `list::insert` inserts elements by copying elements in `O(n)` time.

## random
- `std::random_device` can be used to seed a random number generator.
   - or a time.
- `std::mt19937` - is a pseudo-random generator of 32-bit numbers.
- `std::uniform_int_distribution<int>` - uniform discrete distribution. An instance of `std::mt19937` must passed.
