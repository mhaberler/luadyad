function main(input)
  -- parsing number of arguments (path based)
  input,argCount = string.gsub(input, "/", "%1")
  if ((argCount == 1) and (#input == 1)) then

    return "<html><body><pre>" ..
    "hello world from luadyad" ..
    "</pre></body></html>"

  else

    return "<html><body><pre>" ..
    "path not found ..." ..
    "</pre></body></html>"

  end -- if
end -- function main

