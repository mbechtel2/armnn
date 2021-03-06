//
// Copyright © 2017 Arm Ltd. All rights reserved.
// SPDX-License-Identifier: MIT
//
#pragma once

#include "TypeUtils.hpp"

#include <armnn/INetwork.hpp>

#include <backendsCommon/test/CommonTestUtils.hpp>

#include <boost/test/unit_test.hpp>

#include <vector>

namespace
{

template<typename armnn::DataType DataType>
INetworkPtr CreateMergerNetwork(const std::vector<TensorShape>& inputShapes,
                                const TensorShape& outputShape,
                                unsigned int concatAxis,
                                const float qScale = 1.0f,
                                const int32_t qOffset = 0)
{
    using namespace armnn;
    // Builds up the structure of the network.
    INetworkPtr net(INetwork::Create());

    OriginsDescriptor descriptor;

    descriptor = CreateMergerDescriptorForConcatenation(inputShapes.begin(),
                                                        inputShapes.end(),
                                                        concatAxis);
    IConnectableLayer* merger = net->AddMergerLayer(descriptor, "merger");

    for (unsigned int i = 0; i < inputShapes.size(); ++i)
    {
        TensorInfo inputTensorInfo(inputShapes[i], DataType, qScale, qOffset);
        IConnectableLayer* input = net->AddInputLayer(boost::numeric_cast<LayerBindingId>(i));
        Connect(input, merger, inputTensorInfo, 0, i);
    }

    TensorInfo outputTensorInfo(outputShape, DataType, qScale, qOffset);
    IConnectableLayer* output = net->AddOutputLayer(0, "output");
    Connect(merger, output, outputTensorInfo, 0, 0);

    return net;
}

template<armnn::DataType ArmnnType>
void MergerDim0EndToEnd(const std::vector<BackendId>& backends)
{
    using namespace armnn;
    using T = ResolveType<ArmnnType>;

    unsigned int concatAxis = 0;
    const std::vector<TensorShape> inputShapes{{ 2, 3, 2, 2 }, { 2, 3, 2, 2 }};
    const TensorShape& outputShape = { 4, 3, 2, 2 };

    // Builds up the structure of the network
    INetworkPtr net = CreateMergerNetwork<ArmnnType>(inputShapes, outputShape, concatAxis);

    BOOST_TEST_CHECKPOINT("create a network");

    // Creates structures for input & output.
    std::vector<T> inputData{
        1, 2,
        3, 4,
        5, 6,
        7, 8,
        9, 10,
        11, 12,
        1, 2,
        3, 4,
        5, 6,
        7, 8,
        9, 10,
        11, 12
    };

    std::vector<T> expectedOutput{
        1, 2,
        3, 4,
        5, 6,
        7, 8,
        9, 10,
        11, 12,
        1, 2,
        3, 4,
        5, 6,
        7, 8,
        9, 10,
        11, 12,
        1, 2,
        3, 4,
        5, 6,
        7, 8,
        9, 10,
        11, 12,
        1, 2,
        3, 4,
        5, 6,
        7, 8,
        9, 10,
        11, 12
    };

    std::map<int, std::vector<T>> inputTensorData = {{ 0,inputData }, { 1,inputData }};
    std::map<int, std::vector<T>> expectedOutputData = {{ 0,expectedOutput }};

    EndToEndLayerTestImpl<ArmnnType, ArmnnType>(move(net), inputTensorData, expectedOutputData, backends);
}

template<armnn::DataType ArmnnType>
void MergerDim1EndToEnd(const std::vector<BackendId>& backends)
{
    using namespace armnn;
    using T = ResolveType<ArmnnType>;

    unsigned int concatAxis = 1;
    const std::vector<TensorShape> inputShapes{{ 2, 3, 2, 2 }, { 2, 3, 2, 2 }};
    const TensorShape& outputShape = { 2, 6, 2, 2 };

    // Builds up the structure of the network
    INetworkPtr net = CreateMergerNetwork<ArmnnType>(inputShapes, outputShape, concatAxis);

    BOOST_TEST_CHECKPOINT("create a network");

    // Creates structures for input & output.
    std::vector<T> inputData{
        1, 2,
        3, 4,
        5, 6,
        7, 8,
        9, 10,
        11, 12,
        1, 2,
        3, 4,
        5, 6,
        7, 8,
        9, 10,
        11, 12
    };

    std::vector<T> expectedOutput{
        1, 2,
        3, 4,
        5, 6,
        7, 8,
        9, 10,
        11, 12,
        1, 2,
        3, 4,
        5, 6,
        7, 8,
        9, 10,
        11, 12,
        1, 2,
        3, 4,
        5, 6,
        7, 8,
        9, 10,
        11, 12,
        1, 2,
        3, 4,
        5, 6,
        7, 8,
        9, 10,
        11, 12
    };

    std::map<int, std::vector<T>> inputTensorData = {{ 0,inputData }, { 1,inputData }};
    std::map<int, std::vector<T>> expectedOutputData = {{ 0,expectedOutput }};

    EndToEndLayerTestImpl<ArmnnType, ArmnnType>(move(net), inputTensorData, expectedOutputData, backends);
}

template<armnn::DataType ArmnnType>
void MergerDim2EndToEnd(const std::vector<BackendId>& backends)
{
    using namespace armnn;
    using T = ResolveType<ArmnnType>;

    unsigned int concatAxis = 2;
    const std::vector<TensorShape> inputShapes{{ 2, 3, 2, 2 }, { 2, 3, 2, 2 }};
    const TensorShape& outputShape = { 2, 3, 4, 2 };

    // Builds up the structure of the network
    INetworkPtr net = CreateMergerNetwork<ArmnnType>(inputShapes, outputShape, concatAxis);

    BOOST_TEST_CHECKPOINT("create a network");

    // Creates structures for input & output.
    std::vector<T> inputData{
        1, 2,
        3, 4,
        5, 6,
        7, 8,
        9, 10,
        11, 12,
        1, 2,
        3, 4,
        5, 6,
        7, 8,
        9, 10,
        11, 12
    };

    std::vector<T> expectedOutput{
        1, 2,
        3, 4,
        1, 2,
        3, 4,
        5, 6,
        7, 8,
        5, 6,
        7, 8,
        9, 10,
        11, 12,
        9, 10,
        11, 12,
        1, 2,
        3, 4,
        1, 2,
        3, 4,
        5, 6,
        7, 8,
        5, 6,
        7, 8,
        9, 10,
        11, 12,
        9, 10,
        11, 12
    };

    std::map<int, std::vector<T>> inputTensorData = {{ 0,inputData }, { 1,inputData }};
    std::map<int, std::vector<T>> expectedOutputData = {{ 0,expectedOutput }};

    EndToEndLayerTestImpl<ArmnnType, ArmnnType>(move(net), inputTensorData, expectedOutputData, backends);
}

template<armnn::DataType ArmnnType, typename T = armnn::ResolveType<ArmnnType>>
void MergerDim3EndToEnd(const std::vector<BackendId>& backends)
{
    using namespace armnn;

    unsigned int concatAxis = 3;
    const std::vector<TensorShape> inputShapes{{ 2, 3, 2, 2 }, { 2, 3, 2, 2 }};
    const TensorShape& outputShape = { 2, 3, 2, 4 };

    // Builds up the structure of the network
    INetworkPtr net = CreateMergerNetwork<ArmnnType>(inputShapes, outputShape, concatAxis);

    BOOST_TEST_CHECKPOINT("create a network");

    // Creates structures for input & output.
    std::vector<T> inputData{
        1, 2,
        3, 4,
        5, 6,
        7, 8,
        9, 10,
        11, 12,
        1, 2,
        3, 4,
        5, 6,
        7, 8,
        9, 10,
        11, 12
    };

    std::vector<T> expectedOutput{
        1, 2,
        1, 2,
        3, 4,
        3, 4,
        5, 6,
        5, 6,
        7, 8,
        7, 8,
        9, 10,
        9, 10,
        11, 12,
        11, 12,
        1, 2,
        1, 2,
        3, 4,
        3, 4,
        5, 6,
        5, 6,
        7, 8,
        7, 8,
        9, 10,
        9, 10,
        11, 12,
        11, 12
    };

    std::map<int, std::vector<T>> inputTensorData = {{ 0,inputData }, { 1,inputData }};
    std::map<int, std::vector<T>> expectedOutputData = {{ 0,expectedOutput }};

    EndToEndLayerTestImpl<ArmnnType, ArmnnType>(move(net), inputTensorData, expectedOutputData, backends);
}

} // anonymous namespace
