notification :terminal_notifier

guard :shell do
  watch %r{^(.+\.(?:hpp|cpp))$} do |m|
    puts("\e[1;33m" + '~' * 100 + "\e[0m")
    Dir.glob("tests/**/*.cpp").each do |f|
      puts `g++-4.8 -std=c++11 -Wall -Wextra #{f} && ./a.out && rm a.out`
      puts $?
    end
  end
end
