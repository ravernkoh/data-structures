def main
  begin
    Dir.mkdir("bin")
  rescue
  end

  dirs = Dir.glob("*")
  dirs = dirs.select { |file| File.directory? file }
  dirs.each { |dir| demo dir }
end

def demo(dir)
  files = Dir.glob("#{dir}/*")
  files.each { |file| run dir, file }
end

def run(dir, file)
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