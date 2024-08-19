#pragma once

enum DummyEvent {
    Dummy_ByteInputEvent_Address,
    Dummy_ByteInputEvent_Payload,
    Dummy_Send,
};

enum DummyByteInputScene {
    Dummy_ByteInputScene_Address,
    Dummy_ByteInputScene_Payload,
};

enum DummyVarItemListIndex {
    DummyVarItemListIndexAddress, ///< item to set address of peripheral
    DummyVarItemListIndexTxBytes, ///< item to set number of bytes to send
    DummyVarItemListIndexPayload, ///< item to edit payload
    DummyVarItemListIndexRxBytes, ///< item to set number of bytes to receive
    DummyVarItemListIndexSend,    ///< item to send to sensor
};
