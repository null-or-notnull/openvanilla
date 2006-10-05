#include <vector>
//#include <windows.h>
#include "PCMan.h"


#pragma managed

#using <mscorlib.dll>
#using <System.dll>
#using <System.Windows.Forms.dll>
using namespace System;
using namespace System::Diagnostics;
using namespace System::Reflection;
using namespace System::Windows::Forms;
using namespace System::Collections;
using namespace std;

__gc class CompFormAssembly{
private:
	CompFormAssembly(){}
	static Assembly* pasm;
	static bool hasPasm = false;

	static Object* objCompForm;
	static bool hasObjCompForm = false;

	static Type* typeComp;
	static bool hasTypeComp = false;

	static MethodInfo* methodCompShowNoActive;
	static bool hasMethodCompShowNoActive = false;

	static MethodInfo* methodCompMove;
	static bool hasMethodCompMove = false;

	static MethodInfo* methodCompSetString;
	static bool hasMethodCompSetString = false;

	static MethodInfo* methodCompHide;
	static bool hasMethodCompHide = false;

	static MethodInfo* methodCompClear;
	static bool hasMethodCompClear = false;

	__nogc struct IsFormCreated
	{
		bool isCreated;
		void PutValue(bool flag)
		{
			isCreated = flag;
		}

		bool GetValue()
		{
			return isCreated;
		}
		__declspec(property(get = GetValue, put = PutValue)) bool IsCreated;
	};

public:
	static ArrayList* argCollection = __gc new ArrayList();
	static IsFormCreated* FormStatus=new IsFormCreated();
	static Assembly* Instance()
	{
		if(!hasPasm) 
		{
			pasm = Reflection::Assembly::LoadFile("C:\\WINDOWS\\OpenVanilla\\CSharpFormLibrary.dll");	
			hasPasm = true;
		}
		return pasm;
	}

	static Object* CompForm()
	{
		if(!hasObjCompForm)
		{
			objCompForm =
				pasm->CreateInstance("CSharpFormLibrary.IMECompForm",true);
			hasObjCompForm = true;
		}
		return objCompForm;
	}

	static Type* CompType()
	{
		if(!hasTypeComp)
		{
			typeComp =
				CompFormAssembly::Instance()
					->GetType("CSharpFormLibrary.IMECompForm");
			hasTypeComp = true;
		}
		return typeComp;
	}

	static MethodInfo* CompShowNoActive()
	{
		if(!hasMethodCompShowNoActive)
		{
			methodCompShowNoActive =
				CompFormAssembly::CompType()->GetMethod("ShowNoActive");
			hasMethodCompShowNoActive = true;
		}
		return methodCompShowNoActive;
	}

	static MethodInfo* CompMove()
	{
		if(!hasMethodCompMove)
		{
			methodCompMove =
				CompFormAssembly::CompType()	->GetMethod("SetLocation");
			hasMethodCompMove = true;
		}
		return methodCompMove;
	}

	static MethodInfo* CompSetString()
	{
		if(!hasMethodCompSetString)
		{
			methodCompSetString =
				CompFormAssembly::CompType()	->GetMethod("SetComp");
			hasMethodCompSetString = true;
		}
		return methodCompSetString;
	}

	static MethodInfo* CompHide()
	{
		if(!hasMethodCompHide)
		{
			methodCompHide =
				CompFormAssembly::CompType()	->GetMethod("HideNoActive");
			hasMethodCompHide = true;
		}
		return methodCompHide;
	}

	static MethodInfo* CompClear()
	{
		if(!hasMethodCompClear)
		{
			methodCompClear =
				CompFormAssembly::CompType()	->GetMethod("ClearComp");
			hasMethodCompClear = true;
		}
		return methodCompClear;
	}
};

HWND _CreateCompPage()//create
{	
	//System::Diagnostics::Debug::WriteLine("Comp Create");
	//MethodInfo* methodCreateWindow =
	//	CompFormAssembly::CompType()->GetMethod("IMECompForm");
	
	PropertyInfo* propertyHandle =
		CompFormAssembly::CompType()->GetProperty("Handle");
	return
		(HWND)(
			dynamic_cast<IntPtr*>(
				propertyHandle->GetValue(CompFormAssembly::CompForm(), NULL))
		)->ToPointer();
	
}

void _SetCompString(const std::wstring& Comp)
{
	//System::Diagnostics::Debug::WriteLine("Comp SetString");
	CompFormAssembly::argCollection->Clear();
	CompFormAssembly::argCollection
		->Add(dynamic_cast<Object*>((__gc new System::String(Comp.c_str()))));
	Object* param[] =
		dynamic_cast<Object*[]>(CompFormAssembly::argCollection
			->ToArray(System::Type::GetType("System.Object")));
	CompFormAssembly::CompSetString()->Invoke(CompFormAssembly::CompForm(), param);
}

void _ShowCompPage()
{	
	//System::Diagnostics::Debug::WriteLine("Comp Show");
	//try 
	//{
		//System::Reflection::Assembly* foo = CandFormAssembly::Instance();	
		//System::Type* bar = foo->GetType("CSharpFormLibrary.IMECompForm");
		//MethodInfo* methodShowWindow = bar->GetMethod("ShowNoActive");
		//methodShowWindow->Invoke(CandFormAssembly::CandidateForm(), NULL);
		//Object* ret = CandFormAssembly::CandiShowNoActive()
	Object* ret = CompFormAssembly::CompShowNoActive()
			->Invoke(CompFormAssembly::CompForm(), NULL);
	//}
	/*
	catch(System::Exception* e)
	{
		System::Diagnostics::Debug::WriteLine(e->Source);
		System::Diagnostics::Debug::WriteLine(e->TargetSite);
		System::Diagnostics::Debug::WriteLine(e->HelpLink);
		System::Diagnostics::Debug::WriteLine(e->InnerException);
		System::Diagnostics::Debug::WriteLine(e->Message);
		System::Diagnostics::Debug::WriteLine(e->StackTrace);
	}
	*/
}

void _MoveCompPage(int x,int y)
{	
	//System::Diagnostics::Debug::WriteLine("Candi Move");
	CompFormAssembly::argCollection->Clear();
	CompFormAssembly::argCollection->Add(dynamic_cast<Object*>(__box(x)));
	CompFormAssembly::argCollection->Add(dynamic_cast<Object*>(__box(y)));	

	Object* param[] =
		dynamic_cast<Object*[]>(CompFormAssembly::argCollection
			->ToArray(System::Type::GetType("System.Object")));
	Object* ret =
		CompFormAssembly::CompMove()->Invoke(CompFormAssembly::CompForm(), param);
}

void _HideCompPage()
{
	//System::Diagnostics::Debug::WriteLine("Candi Hide");
	//MethodInfo* methodHideWindow = CompFormAssembly::Instance()->GetType("CSharpFormLibrary.IMECompForm")->	GetMethod("HideNoActive");
	//methodHideWindow->Invoke(CompFormAssembly::CompForm(),NULL);
	CompFormAssembly::CompHide()->Invoke(CompFormAssembly::CompForm(),NULL);
}

void _ClearCompPage()
{
	//System::Diagnostics::Debug::WriteLine("Comp Clear");
	//MethodInfo* methodClearWindow = CompFormAssembly::Instance()->GetType("CSharpFormLibrary.IMECompForm")->GetMethod("ClearComp");
	//methodClearWindow->Invoke(CompFormAssembly::CompForm(),NULL);
	CompFormAssembly::CompClear()->Invoke(CompFormAssembly::CompForm(),NULL);
}

void _EndCompPage()
{
	//����DisposeForm
	//System::Diagnostics::Debug::WriteLine("Comp End");
	MethodInfo* methodDisposeWindow = CompFormAssembly::Instance()->GetType("CSharpFormLibrary.IMECompForm")->GetMethod("DisposeForm");
	methodDisposeWindow->Invoke(CompFormAssembly::CompForm(),NULL);
}

int _GetCompValue()
{
	/*
	MethodInfo* methodGetValue = CompFormAssembly::Instance()->GetType("CSharpFormLibrary.IMECompForm")->GetMethod("GetValue");
	Object* rtnValue = methodGetValue->Invoke(CompFormAssembly::CompForm(),NULL);
	return Convert::ToInt32(rtnValue);
	*/
	return 0;
}

void _ShowCompPageArray(const std::vector<std::wstring>& Comp)
{
	/*
	ArrayList* arrayComp = __gc new ArrayList();
	for(size_t i=0;i<Comp.size();i++)
	{
		std::wstring Comp = Comp.at(i);
		arrayComp->Add(__gc new System::String(Comp.c_str()));
	}
	ArrayList* argCollection = __gc new ArrayList();
	argCollection->Add(dynamic_cast<Object*>(arrayComp));
	MethodInfo* methodShowWindow = CompFormAssembly::Instance()->GetType("CSharpFormLibrary.IMECompForm")->GetMethod("ShowComp");
	methodShowWindow->Invoke(CompFormAssembly::CompForm(),(Object*[])argCollection->ToArray(System::Type::GetType("System.Object")));
	*/
}

/*
void _CreateCompAndSetLocation(int x ,int y) //create and init as (x,y)
{
	MethodInfo* methodCreateWindow = CompFormAssembly::Instance()->GetType("CSharpFormLibrary.IMECompForm")->GetMethod("IMECompForm");
	ArrayList* argCollection = __gc new ArrayList();
	System::Diagnostics::Debug::WriteLine("Create and Set Location");
	argCollection->Add(dynamic_cast<Object*>(__box(x)));
	argCollection->Add(dynamic_cast<Object*>(__box(y)));
	Object* tmp[] = (Object*[])argCollection->ToArray(System::Type::GetType("System.Object"));
	methodShowWindow->Invoke(CompFormAssembly::CompForm(),tmp);
}
*/
