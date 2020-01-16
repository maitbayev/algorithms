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
