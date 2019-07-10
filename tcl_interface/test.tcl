addString "hello"
addString "world"

foreach s [getMyStrings] {
  puts "[$s get] : [$s length]"
}
