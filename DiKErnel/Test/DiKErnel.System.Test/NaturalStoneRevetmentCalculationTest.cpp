// Copyright (C) Stichting Deltares 2022. All rights reserved.
//
// This file is part of DiKErnel.
//
// DiKErnel is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, version 3.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/lgpl-3.0.html>.
//
// All names, logos, and references to "Deltares" are registered trademarks of
// Stichting Deltares and remain full property of Stichting Deltares at all times.
// All rights reserved.

#include <fstream>

#include "AssertHelper.h"
#include "CalculationInputBuilder.h"
#include "CalculationTestBase.h"
#include "TestDefaults.h"

namespace DiKErnel::System::Test
{
	using namespace Core;
	using namespace Integration;
	using namespace std;
	using namespace testing;
	using namespace TestUtil;

	struct NaturalStoneRevetmentCalculationTest : CalculationTestBase
	{
		[[nodiscard]]
		static unique_ptr<CalculationInputBuilder> CreateBuilderForSchematization1()
		{
			auto builder = make_unique<CalculationInputBuilder>();

			builder->AddTimeStep(0, 900, 1.4, 1, 5.5, 30);
			builder->AddTimeStep(900, 1800, 1.6, 1.2, 6, 60);
			builder->AddTimeStep(1800, 2700, 1.7, 1.2, 6.5, 90);
			builder->AddTimeStep(2700, 3600, 1.8, 1.3, 7, 75);
			builder->AddTimeStep(3600, 4500, 2, 1.4, 7, 60);
			builder->AddTimeStep(4500, 5400, 2.1, 1.3, 7.5, 45);
			builder->AddTimeStep(5400, 6300, 2.1, 1.6, 8, 30);
			builder->AddTimeStep(6300, 7200, 2.4, 1.7, 8, 15);
			builder->AddTimeStep(7200, 8100, 2, 2.4, 8.5, 0);
			builder->AddTimeStep(8100, 9000, 1.9, 2.2, 8, 0);
			builder->AddTimeStep(9000, 9900, 1.6, 1.8, 7, 0);
			builder->AddTimeStep(9900, 10800, 1.4, 1.2, 6, 0);

			builder->AddDikeProfileSegment(0, 0, 30, 7.5);

			builder->AddDikeProfilePointData(0, CharacteristicPointType::OuterToe);
			builder->AddDikeProfilePointData(30, CharacteristicPointType::OuterCrest);

			return builder;
		}

		[[nodiscard]]
		static unique_ptr<CalculationInputBuilder> CreateBuilderForSchematization2()
		{
			auto builder = make_unique<CalculationInputBuilder>();

			builder->AddTimeStep(0, 900, 1.4, 1, 5.5, 30);
			builder->AddTimeStep(900, 1800, 1.6, 1.2, 6, 60);
			builder->AddTimeStep(1800, 2700, 1.7, 1.2, 6.5, 90);
			builder->AddTimeStep(2700, 3600, 1.8, 1.3, 7, 75);
			builder->AddTimeStep(3600, 4500, 2, 1.4, 7, 60);
			builder->AddTimeStep(4500, 5400, 2.1, 1.3, 7.5, 45);
			builder->AddTimeStep(5400, 6300, 2.1, 1.6, 8, 30);
			builder->AddTimeStep(6300, 7200, 2.4, 1.7, 8, 15);
			builder->AddTimeStep(7200, 8100, 2, 2.4, 8.5, 0);
			builder->AddTimeStep(8100, 9000, 1.9, 2.2, 8, 0);
			builder->AddTimeStep(9000, 9900, 1.6, 1.8, 7, 0);
			builder->AddTimeStep(9900, 10800, 1.4, 1.2, 6, 0);

			builder->AddDikeProfileSegment(0, 0, 6.4, 1.6);
			builder->AddDikeProfileSegment(6.4, 1.6, 12.4, 1.8);
			builder->AddDikeProfileSegment(12.4, 1.8, 30, 7.5);

			builder->AddDikeProfilePointData(0, CharacteristicPointType::OuterToe);
			builder->AddDikeProfilePointData(6.4, CharacteristicPointType::CrestOuterBerm);
			builder->AddDikeProfilePointData(12.4, CharacteristicPointType::NotchOuterBerm);
			builder->AddDikeProfilePointData(30, CharacteristicPointType::OuterCrest);

			return builder;
		}

		[[nodiscard]]
		static unique_ptr<CalculationInputBuilder> CreateBuilderForSchematization3()
		{
			auto builder = make_unique<CalculationInputBuilder>();

			builder->AddTimeStep(0, 900, 1.4, 1, 5.5, 30);
			builder->AddTimeStep(900, 1800, 1.6, 1.2, 6, 60);
			builder->AddTimeStep(1800, 2700, 1.7, 1.2, 6.5, 90);
			builder->AddTimeStep(2700, 3600, 1.8, 1.3, 7, 75);
			builder->AddTimeStep(3600, 4500, 2, 1.4, 7, 60);
			builder->AddTimeStep(4500, 5400, 2.1, 1.3, 7.5, 45);
			builder->AddTimeStep(5400, 6300, 2.1, 1.6, 8, 30);
			builder->AddTimeStep(6300, 7200, 2.4, 1.7, 8, 15);
			builder->AddTimeStep(7200, 8100, 2, 2.4, 8.5, 0);
			builder->AddTimeStep(8100, 9000, 1.9, 2.2, 8, 0);
			builder->AddTimeStep(9000, 9900, 1.6, 1.8, 7, 0);
			builder->AddTimeStep(9900, 10800, 1.4, 1.2, 6, 0);

			builder->AddDikeProfileSegment(0, 0, 6.4, 1.6);
			builder->AddDikeProfileSegment(6.4, 1.6, 12.4, 1.8);
			builder->AddDikeProfileSegment(12.4, 1.8, 30, 7.5);

			builder->AddDikeProfilePointData(0, CharacteristicPointType::OuterToe);
			builder->AddDikeProfilePointData(30, CharacteristicPointType::OuterCrest);

			return builder;
		}

		[[nodiscard]]
		static unique_ptr<CalculationInputBuilder> CreateBuilderForSchematization4()
		{
			auto builder = make_unique<CalculationInputBuilder>();

			builder->AddTimeStep(0, 900, 1.27, 1.5, 6, 0);
			builder->AddTimeStep(900, 1800, 1.271, 1.5, 6, 0);
			builder->AddTimeStep(1800, 2700, 1.272, 1.5, 6, 0);
			builder->AddTimeStep(2700, 3600, 1.273, 1.5, 6, 0);
			builder->AddTimeStep(3600, 4500, 2.531, 1.5, 6, 0);
			builder->AddTimeStep(4500, 5400, 2.532, 1.5, 6, 0);
			builder->AddTimeStep(5400, 6300, 2.533, 1.5, 6, 0);
			builder->AddTimeStep(6300, 7200, 2.534, 1.5, 6, 0);
			builder->AddTimeStep(7200, 8100, 2.535, 1.5, 6, 0);
			builder->AddTimeStep(8100, 9000, 2.536, 1.5, 6, 0);
			builder->AddTimeStep(9000, 9900, 2.537, 1.5, 6, 0);
			builder->AddTimeStep(9900, 10800, 2.538, 1.5, 6, 0);

			builder->AddDikeProfileSegment(0, 0, 30, 7.5);

			builder->AddDikeProfilePointData(0, CharacteristicPointType::OuterToe);
			builder->AddDikeProfilePointData(30, CharacteristicPointType::OuterCrest);

			return builder;
		}

		[[nodiscard]]
		static unique_ptr<CalculationInputBuilder> CreateBuilderForSchematization5()
		{
			auto builder = make_unique<CalculationInputBuilder>();

			builder->AddTimeStep(-3600, -3420, 1.4, 1, 5.5, 30);
			builder->AddTimeStep(-3420, -3060, 1.6, 1.2, 6, 60);
			builder->AddTimeStep(-3060, -2520, 1.7, 1.2, 6.5, 90);
			builder->AddTimeStep(-2520, -1800, 1.8, 1.3, 7, 75);
			builder->AddTimeStep(-1800, -900, 2, 1.4, 7, 60);
			builder->AddTimeStep(-900, 180, 2.1, 1.3, 7.5, 45);
			builder->AddTimeStep(180, 1440, 2.1, 1.6, 8, 30);
			builder->AddTimeStep(1440, 2880, 2.4, 1.7, 8, 15);
			builder->AddTimeStep(2880, 4500, 2, 2.4, 8.5, 0);
			builder->AddTimeStep(4500, 6300, 1.9, 2.2, 8, 0);
			builder->AddTimeStep(6300, 8280, 1.6, 1.8, 7, 0);
			builder->AddTimeStep(8280, 10800, 1.4, 1.2, 6, 0);

			builder->AddDikeProfileSegment(0, 0, 30, 7.5);

			builder->AddDikeProfilePointData(0, CharacteristicPointType::OuterToe);
			builder->AddDikeProfilePointData(30, CharacteristicPointType::OuterCrest);

			return builder;
		}


#pragma region Schematization 1
		[[nodiscard]]
		static unique_ptr<Util::DataResult<ICalculationInput>> CreateCalculationInputForSchematization1Testcase1()
		{
			// Given
			const auto builder = CreateBuilderForSchematization1();

			auto locationConstructionProperties = make_unique<NaturalStoneRevetmentLocationConstructionProperties>(
				6, NaturalStoneRevetmentTopLayerType::NordicStone, 0.4, 1.65);

			builder->AddNaturalStoneLocation(move(locationConstructionProperties));

			return builder->Build();
		}
		[[nodiscard]]
		static unique_ptr<Util::DataResult<ICalculationInput>> CreateCalculationInputForSchematization1Testcase2()
		{
			// Given
			const auto builder = CreateBuilderForSchematization1();

			auto locationConstructionProperties = make_unique<NaturalStoneRevetmentLocationConstructionProperties>(
				6, NaturalStoneRevetmentTopLayerType::NordicStone, 0.35, 1.6);

			locationConstructionProperties->SetInitialDamage(make_unique<double>(0.6));

			builder->AddNaturalStoneLocation(move(locationConstructionProperties));

			return builder->Build();
		}
		[[nodiscard]]
		static unique_ptr<Util::DataResult<ICalculationInput>> CreateCalculationInputForSchematization1Testcase3()
		{
			// Given
			const auto builder = CreateBuilderForSchematization1();

			auto locationConstructionProperties = make_unique<NaturalStoneRevetmentLocationConstructionProperties>(
				6, NaturalStoneRevetmentTopLayerType::NordicStone, 0.25, 1.65);

			locationConstructionProperties->SetHydraulicLoadXib(make_unique<double>(2.1));
			locationConstructionProperties->SetHydraulicLoadAp(make_unique<double>(6.68));
			locationConstructionProperties->SetHydraulicLoadBp(make_unique<double>(0));
			locationConstructionProperties->SetHydraulicLoadCp(make_unique<double>(0));
			locationConstructionProperties->SetHydraulicLoadNp(make_unique<double>(-0.723));
			locationConstructionProperties->SetHydraulicLoadAs(make_unique<double>(12));
			locationConstructionProperties->SetHydraulicLoadBs(make_unique<double>(1.5));
			locationConstructionProperties->SetHydraulicLoadCs(make_unique<double>(-3.12));
			locationConstructionProperties->SetHydraulicLoadNs(make_unique<double>(-1.5));

			builder->AddNaturalStoneLocation(move(locationConstructionProperties));

			return builder->Build();
		}
		[[nodiscard]]
		static unique_ptr<Util::DataResult<ICalculationInput>> CreateCalculationInputForSchematization1Testcase4()
		{
			// Given
			const auto builder = CreateBuilderForSchematization1();

			auto locationConstructionProperties = make_unique<NaturalStoneRevetmentLocationConstructionProperties>(
				6, NaturalStoneRevetmentTopLayerType::NordicStone, 0.4, 1.65);

			locationConstructionProperties->SetWaveAngleImpactBetamax(make_unique<double>(30));

			builder->AddNaturalStoneLocation(move(locationConstructionProperties));

			return builder->Build();
		}

#pragma endregion

#pragma region Schematization 2
		[[nodiscard]]
		static unique_ptr<Util::DataResult<ICalculationInput>> CreateCalculationInputForSchematization2Testcase1()
		{
			// Given
			const auto builder = CreateBuilderForSchematization2();

			auto locationConstructionProperties = make_unique<NaturalStoneRevetmentLocationConstructionProperties>(
				6, NaturalStoneRevetmentTopLayerType::NordicStone, 0.3, 1.65);

			builder->AddNaturalStoneLocation(move(locationConstructionProperties));

			return builder->Build();
		}
		[[nodiscard]]
		static unique_ptr<Util::DataResult<ICalculationInput>> CreateCalculationInputForSchematization2Testcase2()
		{
			// Given
			const auto builder = CreateBuilderForSchematization2();

			auto locationConstructionProperties = make_unique<NaturalStoneRevetmentLocationConstructionProperties>(
				6, NaturalStoneRevetmentTopLayerType::NordicStone, 0.3, 1.65);

			locationConstructionProperties->SetSlopeUpperLevelAus(make_unique<double>(0.5));
			locationConstructionProperties->SetSlopeLowerLevelAls(make_unique<double>(1));

			builder->AddNaturalStoneLocation(move(locationConstructionProperties));

			return builder->Build();
		}

#pragma endregion

#pragma region Schematization 3
		[[nodiscard]]
		static unique_ptr<Util::DataResult<ICalculationInput>> CreateCalculationInputForSchematization3Testcase1()
		{
			// Given
			const auto builder = CreateBuilderForSchematization3();

			auto locationConstructionProperties = make_unique<NaturalStoneRevetmentLocationConstructionProperties>(
				6, NaturalStoneRevetmentTopLayerType::NordicStone, 0.3, 1.65);

			builder->AddNaturalStoneLocation(move(locationConstructionProperties));

			return builder->Build();
		}

#pragma endregion

#pragma region Schematization 4
		[[nodiscard]]
		static unique_ptr<Util::DataResult<ICalculationInput>> CreateCalculationInputForSchematization4Testcase1()
		{
			// Given
			const auto builder = CreateBuilderForSchematization4();

			auto locationConstructionProperties = make_unique<NaturalStoneRevetmentLocationConstructionProperties>(
				6, NaturalStoneRevetmentTopLayerType::NordicStone, 0.3, 1.65);

			locationConstructionProperties->SetUpperLimitLoadingAul(make_unique<double>(0.08));
			locationConstructionProperties->SetUpperLimitLoadingBul(make_unique<double>(0.7));
			locationConstructionProperties->SetUpperLimitLoadingCul(make_unique<double>(3.5));
			locationConstructionProperties->SetLowerLimitLoadingAll(make_unique<double>(0.08));
			locationConstructionProperties->SetLowerLimitLoadingBll(make_unique<double>(0.15));
			locationConstructionProperties->SetLowerLimitLoadingCll(make_unique<double>(5.5));
			locationConstructionProperties->SetDistanceMaximumWaveElevationAsmax(make_unique<double>(0.5));
			locationConstructionProperties->SetDistanceMaximumWaveElevationBsmax(make_unique<double>(0.8));
			locationConstructionProperties->SetNormativeWidthOfWaveImpactAwi(make_unique<double>(1.1));
			locationConstructionProperties->SetNormativeWidthOfWaveImpactBwi(make_unique<double>(0.15));

			builder->AddNaturalStoneLocation(move(locationConstructionProperties));

			return builder->Build();
		}

#pragma endregion

#pragma region Schematization 5
		[[nodiscard]]
		static unique_ptr<Util::DataResult<ICalculationInput>> CreateCalculationInputForSchematization5Testcase1()
		{
			// Given
			const auto builder = CreateBuilderForSchematization5();

			auto locationConstructionProperties = make_unique<NaturalStoneRevetmentLocationConstructionProperties>(
				6, NaturalStoneRevetmentTopLayerType::NordicStone, 0.4, 1.65);

			builder->AddNaturalStoneLocation(move(locationConstructionProperties));

			return builder->Build();
		}
	};

	TEST_F(NaturalStoneRevetmentCalculationTest, PerformanceTest)
	{
		vector<unique_ptr<Util::DataResult<ICalculationInput>>> calculationInputItems;

		calculationInputItems.push_back(CreateCalculationInputForSchematization1Testcase1());
		calculationInputItems.push_back(CreateCalculationInputForSchematization1Testcase2());
		calculationInputItems.push_back(CreateCalculationInputForSchematization1Testcase3());
		calculationInputItems.push_back(CreateCalculationInputForSchematization1Testcase4());
		calculationInputItems.push_back(CreateCalculationInputForSchematization2Testcase1());
		calculationInputItems.push_back(CreateCalculationInputForSchematization2Testcase2());
		calculationInputItems.push_back(CreateCalculationInputForSchematization3Testcase1());
		calculationInputItems.push_back(CreateCalculationInputForSchematization4Testcase1());
		calculationInputItems.push_back(CreateCalculationInputForSchematization5Testcase1());

		unsigned item = 1;

		ofstream MyFile("PerformanceTestNaturalStoneRevetmentCalculationTest.txt", ios::out | ios::trunc);
		auto startTime = std::chrono::high_resolution_clock::now();
		for (auto const& calculationInputItem : calculationInputItems)
		{
			internal::CaptureStdout();
			PerformTest(calculationInputItem);
			std::string output = internal::GetCapturedStdout();

			MyFile << "Calculation time for test " << item << " is: " << output;
			item++;
		}
		auto endTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> ms_double = endTime - startTime;
		MyFile << "Total Calculation time for NaturalStoneRevetmentCalculationTest is: " << ms_double.count() << " milli seconds" << "\n";
		MyFile << "Average calculation time per NaturalStoneRevetmentCalculationTest is: " << ms_double.count() / (item * TestDefaults::GetNumberOfTestRuns()) << " milli seconds" << "\n";
		MyFile.close();
	}

	//TEST_F(NaturalStoneRevetmentCalculationTest, GrassRevetmentWaveImpactCalculationTest, PerformanceTestAll)
	//{
	//	vector<unique_ptr<Util::DataResult<ICalculationInput>>> calculationInputItems;
	//	// NatuurStone
	//	calculationInputItems.push_back(CreateCalculationInputForSchematization1Testcase1());
	//	calculationInputItems.push_back(CreateCalculationInputForSchematization1Testcase2());
	//	calculationInputItems.push_back(CreateCalculationInputForSchematization1Testcase3());
	//	calculationInputItems.push_back(CreateCalculationInputForSchematization1Testcase4());
	//	calculationInputItems.push_back(CreateCalculationInputForSchematization2Testcase1());
	//	calculationInputItems.push_back(CreateCalculationInputForSchematization2Testcase2());
	//	calculationInputItems.push_back(CreateCalculationInputForSchematization3Testcase1());
	//	calculationInputItems.push_back(CreateCalculationInputForSchematization4Testcase1());
	//	calculationInputItems.push_back(CreateCalculationInputForSchematization5Testcase1());

	//	//GrassRevetmen
	//	calculationInputItems.push_back(CreateCalculationInputForSchematization1Testcase1());
	//	calculationInputItems.push_back(CreateCalculationInputForSchematization1Testcase2());
	//	calculationInputItems.push_back(CreateCalculationInputForSchematization1Testcase3());
	//	calculationInputItems.push_back(CreateCalculationInputForSchematization1Testcase4());
	//	calculationInputItems.push_back(CreateCalculationInputForSchematization1Testcase5());

	//	unsigned item = 1;

	//	ofstream MyFile("PerformanceTestNaturalStoneRevetmentCalculationTest.txt", ios::out | ios::trunc);
	//	auto startTime = std::chrono::high_resolution_clock::now();
	//	for (auto const& calculationInputItem : calculationInputItems)
	//	{
	//		internal::CaptureStdout();
	//		PerformTest(calculationInputItem);
	//		std::string output = internal::GetCapturedStdout();

	//		MyFile << "Calculation time for test " << item << " is: " << output;
	//		item++;
	//	}
	//	auto endTime = std::chrono::high_resolution_clock::now();
	//	std::chrono::duration<double, std::milli> ms_double = endTime - startTime;
	//	MyFile << "Total Calculation time for NaturalStoneRevetmentCalculationTest is: " << ms_double.count() << " milli seconds" << "\n";
	//	MyFile << "Average calculation time per NaturalStoneRevetmentCalculationTest is: " << ms_double.count() / (item * TestDefaults::GetNumberOfTestRuns()) << " milli seconds" << "\n";
	//	MyFile.close();
	//}

#pragma endregion
}
