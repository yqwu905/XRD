keyList = ["PDF", "UnitCell", "d-I-List", "Name", "Formula", "ChemicalClass", "Wavelength", "Filter", "AngleLimit", "Reference", "CAS-Number", "Source", "SpaceGroup", "a", "b", "c", "Alpha", "Beta", "Gamma", "PearsonSymbol", "CalculatedDensity", "MeasuredDensity", "MolecularWeight", "Volume", "Reference", "StrongLines", "Comment"]

d = Dict{AbstractString, Int}()
for key in keyList
	d[key] = 0
end

files = readdir(".")
for file in files
	content = read(`cat $(file)`, String)
	for key in keyList
		if match(Regex(key), content)==nothing
			d[key] = d[key] + 1
			println("$(file) missing $(key).")
		end
	end
end

print(d)
