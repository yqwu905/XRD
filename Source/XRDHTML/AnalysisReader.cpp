// Fill out your copyright notice in the Description page of Project Settings.


#include "AnalysisReader.h"

// Sets default values
AAnalysisReader::AAnalysisReader()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAnalysisReader::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAnalysisReader::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAnalysisReader::LoadXMLFile(const FString &filename)
{
	HitList = new FXmlFile(FPaths::GameContentDir() + "data/" + filename + ".xml");
}



TArray<FHitMaterial> AAnalysisReader::GetHitList()
{
	int num = 0;
	TArray<FHitMaterial> result;
	FXmlNode* rootNode = HitList->GetRootNode();
	FXmlNode* phaseListNode = rootNode->FindChildNode("Pattern")->FindChildNode("PhaseListing");
	auto phaseList = phaseListNode->GetChildrenNodes();
	for (auto node : phaseList)
	{
		num += 1;
		FHitMaterial p;
		p.id = node->GetAttribute("id");;
		auto properties = node->GetChildrenNodes();
		for (auto property : properties)
		{
			if (property->GetTag()=="Formula")
				p.Formula = property->GetContent();
			if (property->GetTag() == "FOM")
				p.FOM = property->GetContent();
			if (property->GetTag() == "y-Scaling")
				p.yScaling = property->GetContent();
			if (property->GetTag() == "d-Scaling")
				p.dScaling = property->GetContent();
			if (property->GetTag() == "x-Offset")
				p.xOffset = property->GetContent();
			if (property->GetTag() == "Card")
				p.Card = property->GetContent();
			if (property->GetTag() == "d-I-LineCount")
				p.dILineCount = property->GetContent();
			if (property->GetTag() == "QualityMark")
				p.QualityMark = property->GetContent();
			if (property->GetTag() == "Source")
				p.Source = property->GetContent();
			if (property->GetTag() == "SpaceGroup")
				p.SpaceGroup = property->GetContent();
			if (property->GetTag() == "PearsonSymbol")
				p.PearsonSymbol = property->GetContent();
			if (property->GetTag() == "RIR")
				p.PIR = property->GetContent();
			if (property->GetTag() == "Density")
				p.Density = property->GetContent();
			if (property->GetTag() == "FormulaUnits")
				p.FormulaUnits = property->GetContent();
			if (property->GetTag() == "a")
				p.a = property->GetContent();
			if (property->GetTag() == "b")
				p.b = property->GetContent();
			if (property->GetTag() == "c")
				p.c = property->GetContent();
			if (property->GetTag() == "Alpha")
				p.alpha = property->GetContent();
			if (property->GetTag() == "Beta")
				p.beta = property->GetContent();
			if (property->GetTag() == "Gamma")
				p.gamma = property->GetContent();
			if (property->GetTag() == "Volume")
				p.volume = property->GetContent();
			if (property->GetTag() == "CSD-Number")
				p.CSDNumber = property->GetContent();
		}
		result.Add(p);
		if (num >= 18)
			break;
	}
	return result;
}

FPDFCard AAnalysisReader::LoadPDFFile(const FString &cardpath)
{
	FXmlFile* PDFCard = new FXmlFile(FPaths::GameContentDir() + "data/PDFCard/" + cardpath + ".xml");
	FXmlNode* rootNode = PDFCard->GetRootNode();
	FXmlNode* cardNode = rootNode->FindChildNode("PDF");
	FXmlNode* unitcellNode = cardNode->FindChildNode("UnitCell");
	FXmlNode* peakNode = cardNode->FindChildNode("d-I-List");
	FPDFCard card;
	card.infos.Add(cardNode->FindChildNode("Name")->GetContent());
	card.infos.Add(cardNode->FindChildNode("Formula")->GetContent());
	if(cardNode->FindChildNode("ChemicalClass")!=NULL)
	{
		card.infos.Add(cardNode->FindChildNode("ChemicalClass")->GetContent());
	}
	else { card.infos.Add(""); }
	card.infos.Add("Radiation=" + cardNode->FindChildNode("Wavelength")->GetAttribute("Source"));
	card.infos.Add("Lambda=" + cardNode->FindChildNode("Wavelength")->GetContent());
	if (cardNode->FindChildNode("Filter") != NULL)
	{
		card.infos.Add("Filter=" + cardNode->FindChildNode("Filter")->GetContent());
	}
	else{ card.infos.Add(""); }
	card.infos.Add("2T=" + cardNode->FindChildNode("AngleLimit")->GetContent());
	card.infos.Add("I/Ic(RIR)=" + peakNode->GetAttribute("RIR"));
	card.infos.Add("Ref: " + cardNode->FindChildNode("Reference")->GetContent());
	if (cardNode->FindChildNode("CAS-Number") != NULL)
	{
		card.infos.Add("CAS#: " + cardNode->FindChildNode("CAS-Number")->GetContent());
	}
	else { card.infos.Add(""); }
	
	card.infos.Add(unitcellNode->GetAttribute("System") + "-" + unitcellNode->FindChildNode("Source")->GetContent() + " " + 
		unitcellNode->FindChildNode("SpaceGroup")->GetContent());
	card.infos.Add("CELL: " + unitcellNode->FindChildNode("a")->GetContent() + "x" + unitcellNode->FindChildNode("b")->GetContent() + "x" + 
		unitcellNode->FindChildNode("b")->GetContent() + "x" + unitcellNode->FindChildNode("c")->GetContent() + "<" + 
		unitcellNode->FindChildNode("Alpha")->GetContent() + "x" + unitcellNode->FindChildNode("Beta")->GetContent() + "x" + 
		unitcellNode->FindChildNode("Gamma")->GetContent() + ">");
	if (cardNode->FindChildNode("PearsonSymbol") != NULL)
	{
		card.infos.Add("P.S=" + unitcellNode->FindChildNode("PearsonSymbol")->GetContent());
	}
	else { card.infos.Add(""); }
	card.infos.Add("Density(c)=" + unitcellNode->FindChildNode("CalculatedDensity")->GetContent());
	if (cardNode->FindChildNode("Comment") != NULL)
	{
		card.infos.Add("Density(m)=" + unitcellNode->FindChildNode("MeasuredDensity")->GetContent());
	}
	else { card.infos.Add(""); }
	if (cardNode->FindChildNode("MolecularWeight") != NULL)
	{
		card.infos.Add("Mwt=" + unitcellNode->FindChildNode("MolecularWeight")->GetContent());
	}
	else { card.infos.Add(""); }

	card.infos.Add("Vol=" + unitcellNode->FindChildNode("Volume")->GetContent());
	card.infos.Add("Ref:" + unitcellNode->FindChildNode("Reference")->GetContent());
	card.infos.Add("Strong Lines:" + cardNode->FindChildNode("StrongLines")->GetContent());
	if (cardNode->FindChildNode("Comment") != NULL)
	{
		card.infos.Add("NOTE: " + cardNode->FindChildNode("Comment")->GetContent());
	}
	else { card.infos.Add(""); }
	return card;
}