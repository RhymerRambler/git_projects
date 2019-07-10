load "./my_string.so"
addString "hello"
addString "world"

foreach s [getMyStrings] {
  puts "[$s get] : [$s length]"
}
