require 'terminfo'

notification :terminal_notifier

def separator
  "\e[1;33m" + '~' * (TermInfo.screen_size[1]-1) + "\e[0m"
end

def compile f
  `g++-4.8 -std=c++11 -Wall -Wextra -pedantic #{f} && ./a.out && rm a.out`
end

def which cmd
  dir = ENV['PATH'].split(':').find {|p| File.executable? File.join(p, cmd)}
  File.join(dir, cmd) unless dir.nil?
end

def notify failed
  msg = "'#{failed} tests failed.\n#{Time.now.to_s}'"
  case
  when which('terminal-notifier')
    `terminal-notifier -message #{msg}`
  when which('notify-send')
    `notify-send #{msg}`
  end
end

guard :shell do
  watch %r{^.+\.(?:hpp|cpp)$} do
    puts separator
    failed, total = 0, 0
    log = Dir.glob("tests/**/*.cpp").map do |f|
      result = compile f
      failed += 1 unless $?.success?
      total += 1
      "test for #{f}\n#{result}#{$?.to_s}"
    end.join("\n") + (failed==0 ? "\nSuccess!" : "\n#{failed} failed (#{failed}/#{total})")
    notify failed if failed > 0
    log
  end
end
