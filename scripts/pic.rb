require 'trollop'
require 'awesome_print'

opts = Trollop::options do
  opt :depth    , 'Bit depth'             , type: :integer  , default: 8
  opt :size     , 'Size in (axb) pixels'  , type: :string
  opt :out      , 'Output filename'       , type: :string   , default: 'out.jpg'

  opt :rgb      , 'RGB'                                     , default: true
  opt :gray     , 'Grayscale'                               , default: false
end

if ARGV.length != 1
  abort "Example: ruby pic.rb --size 300x400 [--depth 8] [--rgb] [--out output.jpg] input.raw"
end

type = nil
types = {
  gray:   opts[:gray],
  rgb:    opts[:rgb]
}

types.each do |k, v|
  if v
    type = k
    break
  end
end

system("convert -size #{opts[:size]} -depth #{opts[:depth]} #{type}:#{ARGV[0]} #{opts[:out]}")