var plot_data = [];

var page_source={};

function loadSource()
{
	urlParams = new URLSearchParams(window.location.search);
	id = urlParams.get('id');
	
	//console.log(id);
	
	page_source.hit_list=HIT_LIST[URL_DICT[id]["HIT_LIST"]];
	page_source.hit_data=HIT_DATA[URL_DICT[id]["HIT_DATA"]];
}

function loadGraph()
{
	var dataSeries = { type: "line" };
	
	dataSeries.dataPoints = page_source.hit_data;
	plot_data.push(dataSeries);
}

function loadTable()
{
	var HEADING="<tr><th>Name</th><th>Chemical Formula</th><th>FOM</th><th>PDF</th><th>RIR</th><th>Space Group</th></tr>"
	var LINE="<tr class=\"list\" _0_><td>_1_</td><td>_2_</td><td>_3_</td><td>_4_</td><td>_5_</td><td>_6_</td></tr>"
	
	function loadLine(obj)
	{
		//console.log(obj);
		line=LINE;
		
		s="";
		
		s='ondblclick="showMaterialData(\''+obj.getElementsByTagName("Card")[0].innerHTML+'\')"';
		line=line.replace("_0_", s);
		
		s=obj.getAttribute("id");
		line=line.replace("_1_", s);
		
		s=obj.getElementsByTagName("Formula")[0].innerHTML;
		line=line.replace("_2_", s);
		
		s=obj.getElementsByTagName("FOM")[0].innerHTML;
		line=line.replace("_3_", s);
		
		s=obj.getElementsByTagName("Card")[0].innerHTML;
		line=line.replace("_4_", s);
		
		s=obj.getElementsByTagName("RIR")[0]?obj.getElementsByTagName("RIR")[0].innerHTML:"-";
		line=line.replace("_5_", s);
		
		s=obj.getElementsByTagName("SpaceGroup")[0].innerHTML;
		line=line.replace("_6_", s);
		
		return line;
	}
	
	var content="";
	content+=HEADING;
	
	parser = new DOMParser();
	x0 = parser.parseFromString(page_source.hit_list,"text/xml");
	
	x1 = x0.getElementsByTagName("MDI")[0].getElementsByTagName("Pattern")[0].getElementsByTagName("PhaseListing")[0].getElementsByTagName("Phase");
	
	//console.log(x1);
	for(i=0; i<x1.length; i++)
	{
		line=loadLine(x1[i]);
		content+=line;
	}
	
	document.getElementById("component_table").innerHTML = content;
	// pp=document.getElementById("component_table");//.innerHTML = "";
}

function showMaterialData(_materialId)
{
	function getData(obj)
	{
		console.log(obj);
		
		data="";
		
		data+="<h3>Reference</h3>";
		data+="<hr>";
		data+="<p>Name: _1_</p>";
		data+="<p>Formula: _2_</p>";
		data+="<hr>";
		data+="<p>Radiation=_3_</p>";
		data+="<p>Lambda=_4_</p>";
		data+="<p>_5_ - Powder Diffraction, _6_&nbsp;&nbsp;&nbsp;&nbsp;Z=_7_</p>";
		data+="<p>CELL: _8_ x _9_ x _10_&nbsp;&nbsp;&nbsp;&nbsp;\<_11_ x _12_ x _13_\>&nbsp;&nbsp;&nbsp;&nbsp;P.S=_14_</p>";
		data+="<p>Density(c)=_15_&nbsp;&nbsp;&nbsp;&nbsp;Density(m)=_16_&nbsp;&nbsp;&nbsp;&nbsp;Mwt=_17_</p>";
		data+="<hr>";
		data+="<p>Reference: _18_</p>";
		
		s=obj.getElementsByTagName("Name")[0].innerHTML;
		data=data.replace("_1_",s);
		
		s=obj.getElementsByTagName("Formula")[0].innerHTML;
		data=data.replace("_2_",s);
		
		s=obj.getElementsByTagName("Wavelength")[0].getAttribute("Source");
		data=data.replace("_3_",s);
		
		s=obj.getElementsByTagName("Wavelength")[0].innerHTML;
		data=data.replace("_4_",s);
		
		s=obj.getElementsByTagName("UnitCell")[0].getAttribute("System");
		data=data.replace("_5_",s);
		
		s=obj.getElementsByTagName("UnitCell")[0].getElementsByTagName("SpaceGroup")[0].innerHTML;
		data=data.replace("_6_",s);
		
		s=obj.getElementsByTagName("UnitCell")[0].getElementsByTagName("FormulaUnits")[0].innerHTML;
		data=data.replace("_7_",s);
		
		s=obj.getElementsByTagName("UnitCell")[0].getElementsByTagName("a")[0].innerHTML;
		data=data.replace("_8_",s);
		
		s=obj.getElementsByTagName("UnitCell")[0].getElementsByTagName("b")[0].innerHTML;
		data=data.replace("_9_",s);
		
		s=obj.getElementsByTagName("UnitCell")[0].getElementsByTagName("c")[0].innerHTML;
		data=data.replace("_10_",s);
		
		s=obj.getElementsByTagName("UnitCell")[0].getElementsByTagName("Alpha")[0].innerHTML;
		data=data.replace("_11_",s);
		
		s=obj.getElementsByTagName("UnitCell")[0].getElementsByTagName("Beta")[0].innerHTML;
		data=data.replace("_12_",s);
		
		s=obj.getElementsByTagName("UnitCell")[0].getElementsByTagName("Gamma")[0].innerHTML;
		data=data.replace("_13_",s);
		
		s=obj.getElementsByTagName("UnitCell")[0].getElementsByTagName("PearsonSymbol")[0].innerHTML;
		data=data.replace("_14_",s);
		
		s=obj.getElementsByTagName("UnitCell")[0].getElementsByTagName("CalculatedDensity")[0].innerHTML;
		data=data.replace("_15_",s);
		
		s=obj.getElementsByTagName("UnitCell")[0].getElementsByTagName("MeasuredDensity")[0].innerHTML;
		data=data.replace("_16_",s);
		
		s=obj.getElementsByTagName("UnitCell")[0].getElementsByTagName("MolecularWeight")[0].innerHTML;
		data=data.replace("_17_",s);
		
		s=obj.getElementsByTagName("UnitCell")[0].getElementsByTagName("Reference")[0].innerHTML;
		data=data.replace("_18_",s);
		
		
		
		return data;
	}
	
	var data;
	
	xml=MATERIAL_DATA[_materialId];
	if(!xml)
	{
		data="<h3>该成分数据缺失!</h3>";
	}
	else
	{
		parser = new DOMParser();
		x0 = parser.parseFromString(xml,"text/xml");
		x1=x0.getElementsByTagName("MDI")[0].getElementsByTagName("PDF")[0];
		
		data=getData(x1);
	}
	
	var modal = document.getElementById("myModal");
	modal.getElementsByTagName("div")[0].getElementsByTagName("div")[0].innerHTML=data;
	
	modal.style.display = "block";
}
