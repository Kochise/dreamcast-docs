
#using <mscorlib.dll>
#using <System.dll>

using namespace System;

#using <System.Xml.dll>
using namespace System::Xml;

#using <System.Drawing.dll>
using namespace System::Drawing;

using namespace System::Diagnostics;


int main()
{
    XmlDocument* xmlDoc = new XmlDocument();

    try
    {
        xmlDoc->Load(S"sample.xml");
        Console::WriteLine(S"Document loaded ok." );
        XmlNodeList* items = xmlDoc->GetElementsByTagName(S"Item");
        double total = 0;
        long numitems = items->Count;
        for (int i=0;i<numitems;i++)
        {
            XmlNode* item = items->Item(i);
            double price = Double::Parse(item->Attributes->GetNamedItem(S"Price")->get_Value());
            double qty = Double::Parse(item->Attributes->GetNamedItem(S"Quantity")->get_Value());
            total += price * qty;
        }
        Console::WriteLine(S"Purchase Order total is ${0}", __box(total));
    }
    catch (Exception *e)
    {
        Console::WriteLine(S"problem loading XML");
        Console::WriteLine(e->Message);
    }
	try
	{
		Image* image = Image::FromFile(S"largepicture.jpg");
        	Image* thumbnail = image->GetThumbnailImage(100,100,0,0);
        	thumbnail->Save(S"thumbnail.jpg",Imaging::ImageFormat::Jpeg);
        	Console::WriteLine(S"Thumbnail created");
	}
	catch (Exception* e)
	{
		// out of memory exception thrown for bad format
        	Console::WriteLine(S"Image file not found or invalid format");
        	Console::WriteLine(e->Message);
	}

    try
    {
        if (! EventLog::SourceExists(S"SDKSample") )
            EventLog::CreateEventSource(S"SDKSample",S"SDKSampleLog");
        EventLog::WriteEntry(S"SDKSample",S"The sample has been run.", EventLogEntryType::Information);
        Console::WriteLine(S"Event logged");
    }
	catch (Exception* e)
	{
		Console::WriteLine(S"problem creating or writing to event log");
        	Console::WriteLine(e->Message);
	}

    return 0;
}