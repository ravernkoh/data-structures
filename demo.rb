def main
  filter = nil
  if ARGV.count > 0
    filter = ARGV[0]
  end

  begin
    Dir.mkdir("bin")
  rescue
  end

  dirs = Dir.glob("*")
  dirs = dirs.select { |file| File.directory? file }
  dirs.each { |dir| demo dir, filter }
end

def demo(dir, filter)
  files = Dir.glob("#{dir}/*")
  files.each { |file| run file, filter }
end

def run(file, filter)
  if filter && !(file.include? filter)
    return
  end

  case true
  when file.end_with?(".cpp")
    puts "-> Compiling #{file}..."
    `g++ #{file} -o bin/a.out`
    puts "-> Running #{file}..."
    system("bin/a.out")
    File.delete("bin/a.out")
  end
end

main