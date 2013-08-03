notification :terminal_notifier

guard :shell do
  watch %r{^(.+\.(?:hpp|cpp))$} do |m|
    puts m[0]
    puts("\e[1;33m" + '~' * 100 + "\e[0m")
    `g++-4.8 -std=c++11 -Wall -Wextra #{m[0]} && ./a.out && rm a.out`
  end
end
