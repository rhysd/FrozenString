require 'terminfo'

notification :terminal_notifier

def separator
  "\e[1;33m" + '~' * (TermInfo.screen_size[1]-1) + "\e[0m"
end

def gcc f
  system "g++-4.8 -std=c++11 -Wall -Wextra -pedantic #{f} && ./a.out && rm a.out"
  $?.success?
end

def clang f
  system "clang++ -std=c++11 -stdlib=libc++ -Wall -Wextra #{f} && ./a.out && rm a.out"
  $?.success?
end

def compile file
  print "    using g++-4.8..."
  a = gcc file

  print "    using clang++..."
  b = clang file

  a && b
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
    puts Time.now.to_s

    failed, total = 0, 0
    Dir.glob("tests/**/*.cpp").map do |f|
      puts "test for #{f}"
      result = compile f
      failed += 1 unless result
      total += 1
    end

    notify failed if failed > 0
    (failed==0 ? "\nSuccess!" : "\n#{failed} failed (#{failed}/#{total})")
  end
end
