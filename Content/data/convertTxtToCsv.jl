txtFilename = ARGS[1]
csvFilename = "$(join(split(txtFilename, ".")[1:end - 1])).csv"
lines = readlines(txtFilename)[2:end]
open(csvFilename, "w") do f
	i = 0
	for line in lines
		data = split(line, " ")
		write(f, "$(i),$(data[1]),$(data[end])\n")
	end
end

