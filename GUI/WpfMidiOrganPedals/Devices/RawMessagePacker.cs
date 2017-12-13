using System;

namespace WpfMidiOrganPedals.Devices
{
    internal class RawMessagePacker : RawMessageHandler
    {
        internal byte[] Pack(byte id, byte[] payloadData)
        {
            var result = new byte[4 + payloadData.Length];

            result[0] = StartByte;
            result[1] = id;
            result[2] = (byte)payloadData.Length;
            result[3] = CalcChecksum(payloadData);
            Array.Copy(payloadData, 0, result, 4, payloadData.Length);

            return result;
        }
    }
}
