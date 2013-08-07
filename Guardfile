require 'terminfo'

notification :terminal_notifier

def separator
  "\e[1;33m" + '~' * (TermInfo.screen_size[1]-1) + "\e[0m"
end

def compile f
  `g++-4.8 -std=c++11 -Wall -Wextra -pedantic #{f} && ./a.out && rm a.out`
end

guard :shell do
  watch %r{^.+\.(?:hpp|cpp)$} do
    puts separator
    failed, total = 0, 0
    Dir.glob("tests/**/*.cpp").map do |f|
      result = compile f
      failed += 1 unless $?.success?
      total += 1
      "test for #{f}\n#{result}#{$?.to_s}"
    end.join("\n") + (failed==0 ? "\nSuccess!" : "\n#{failed} failed (#{failed}/#{total})")
  end
end
