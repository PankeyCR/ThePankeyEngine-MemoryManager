
#ifndef TR_InvokeCommandList_Testing_hpp
	#define TR_InvokeCommandList_Testing_hpp
	
	#include "pankey_HolderSystem.hpp"

	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "InvokeCommandList.hpp"

	namespace pankey{

		namespace HolderSystem{

			class TestCommandList : Base::Command<Base::TestResult&>{
				void execute(Base::TestResult& a_result){
					a_result.assertTrue("executing method", true);
				}
			};

			class TestCommandList_2 : Base::Command<Base::TestResult&>{
				void execute(Base::TestResult& a_result){
					a_result.assertEqual("executing method", 1,1);
				}
			};

			class TestCommandListWithError : Base::Command<Base::TestResult&>{
				void execute(Base::TestResult& a_result){
					a_result.assertTrue("executing method with error", false);
				}
			};
			
			Base::TestResult TR_InvokeCommandList_Testing_1(){
				Base::TestResult result;

				CommandList<> i_list;

				result.assertTrue("list has to be empty", i_list.isEmpty());
				
				return result;
			}
			
			Base::TestResult TR_InvokeCommandList_Testing_2(){
				Base::TestResult result;

				CommandList<float> i_list;

				result.assertTrue("list has to be empty", i_list.isEmpty());
				
				return result;
			}
			
			Base::TestResult TR_InvokeCommandList_Testing_3(){
				Base::TestResult result;

				CommandList<Base::TestResult&> i_list;

				command<Base::TestResult&> i_obj = TestCommandList();

				i_list.add(i_obj);

				invoke<Base::TestResult&>(i_list, 0, result);
				
				return result;
			}
			
			Base::TestResult TR_InvokeCommandList_Testing_4(){
				Base::TestResult result;

				CommandList<Base::TestResult&> i_list;

				command<Base::TestResult&> i_obj = TestCommandList();
				command<Base::TestResult&> i_obj_2 = TestCommandList_2();

				i_list.add(i_obj);
				i_list.add(i_obj_2);

				invokeAll<Base::TestResult&>(i_list, result);
				
				return result;
			}

			class TestCommandListReturn : Base::CommandReturn<bool,bool>{
				bool execute(bool a_bool){
					return a_bool;
				}
			};

			class TestCommandListReturn_2 : Base::CommandReturn<bool,bool,Base::TestResult&>{
				bool execute(bool a_bool, Base::TestResult& a_result){
					a_result.assertTrue("bool parameter has to be true", a_bool);
					return a_bool;
				}
			};

			class TestCommandListReturn_3 : Base::CommandReturn<bool,bool,Base::TestResult&>{
				bool execute(bool a_bool, Base::TestResult& a_result){
					a_result.assertEqual("bool parameter has to be true", a_bool, true);
					return a_bool;
				}
			};

			Base::TestResult TR_InvokeCommandList_Testing_5(){
				Base::TestResult result;

				CommandReturnList<bool,bool> i_list;

				commandReturn<bool,bool> i_obj = TestCommandListReturn();

				i_list.add(i_obj);

				result.assertTrue("command has to return true", invoke(i_list, 0, true));
				
				return result;
			}
			
			Base::TestResult TR_InvokeCommandList_Testing_6(){
				Base::TestResult result;

				CommandReturnList<bool,bool,Base::TestResult&> i_list;

				commandReturn<bool,bool,Base::TestResult&> i_obj = TestCommandListReturn_2();
				commandReturn<bool,bool,Base::TestResult&> i_obj_2 = TestCommandListReturn_3();

				i_list.add(i_obj);
				i_list.add(i_obj_2);

				invokeAll<bool,bool,Base::TestResult&>(i_list, true, result);
				
				return result;
			}

			void TR_InvokeCommandList_Testing(Base::TestRunner& a_test_runner){
				createMemoryManager();

				a_test_runner.add("CommandList Constructor with no arguments", TR_InvokeCommandList_Testing_1);
				a_test_runner.add("CommandList Constructor with 1 float arguments", TR_InvokeCommandList_Testing_2);
				a_test_runner.add("CommandList invoke with Base::TestResult& argument", TR_InvokeCommandList_Testing_3);
				a_test_runner.add("CommandList invokeAll with Base::TestResult& argument", TR_InvokeCommandList_Testing_4);
				a_test_runner.add("CommandList invoke class with Base::TestResult& argument", TR_InvokeCommandList_Testing_5);
				a_test_runner.add("CommandList invokeAll class with Base::TestResult& argument", TR_InvokeCommandList_Testing_6);
			}

		}

	}

#endif
