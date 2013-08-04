require 'terminfo'

notification :terminal_notifier

guard :shell do
  watch %r{^(.+\.(?:hpp|cpp))$} do |m|
    puts("\e[1;33m" + '~' * TermInfo.screen_size[1] + "\e[0m")
    Dir.glob("tests/**/*.cpp").map do |f|
      `g++-4.8 -std=c++11 -Wall -Wextra -pedantic #{f} && ./a.out && rm a.out` + $?.to_s
    end.join("\n")
  end
end
