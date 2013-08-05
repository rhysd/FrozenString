require 'terminfo'

notification :terminal_notifier

guard :shell do
  watch %r{^.+\.(?:hpp|cpp)$} do
    puts("\e[1;33m" + '~' * (TermInfo.screen_size[1]-1) + "\e[0m")
    failed = 0
    total = 0
    Dir.glob("tests/**/*.cpp").map do |f|
      result = `g++-4.8 -std=c++11 -Wall -Wextra -pedantic #{f} && ./a.out && rm a.out`
      failed += 1 unless $?.success?
      total += 1
      "test for #{f}\n#{result}#{$?.to_s}"
    end.join("\n") + (failed==0 ? "\nSuccess!" : "\n#{failed} failed (#{failed}/#{total})")
  end
end
