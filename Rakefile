require 'rake'
require 'rake/testtask'
require 'rake/clean'

CS_ROOT = 'ext/callsite'

desc 'Default: test'
task :default => :test

desc 'Run callsite tests.'
Rake::TestTask.new(:test) do |t|
  t.libs = [CS_ROOT]
  t.pattern = 'test/test_*.rb'
  t.verbose = true
end
task :test => :build

namespace :build do
  file "#{CS_ROOT}/callsite.c"
  file "#{CS_ROOT}/extconf.rb"
  file "#{CS_ROOT}/Makefile" => %W(#{CS_ROOT}/callsite.c #{CS_ROOT}/extconf.rb) do
    Dir.chdir(CS_ROOT) do
      ruby 'extconf.rb'
    end
  end

  desc "generate makefile"
  task :makefile => %W(#{CS_ROOT}/Makefile #{CS_ROOT}/callsite.c)

  dlext = Config::CONFIG['DLEXT']
  file "#{CS_ROOT}/callsite.#{dlext}" => %W(#{CS_ROOT}/Makefile #{CS_ROOT}/callsite.c) do
    Dir.chdir(CS_ROOT) do
      sh 'make' # TODO - is there a config for which make somewhere?
    end
  end

  desc "compile callsite extension"
  task :compile => "#{CS_ROOT}/callsite.#{dlext}"

  task :clean do
    Dir.chdir(CS_ROOT) do
      sh 'make clean'
    end if File.exists?("#{CS_ROOT}/Makefile")
  end

  CLEAN.include("#{CS_ROOT}/Makefile")
  CLEAN.include("#{CS_ROOT}/callsite.#{dlext}")
end

task :clean => %w(build:clean)

desc "compile"
task :build => %w(build:compile)

task :install do |t|
  Dir.chdir(CS_ROOT) do
    sh 'sudo make install'
  end
end

desc "clean build install"
task :setup => %w(clean build install)

desc "run benchmarks"
task :bench do |t|
  sh "ruby bench/bench.rb"  
end