using System;
using System.Collections.Generic;

namespace WpfMidiOrganPedals.Devices
{
    internal class RawMessageBuilder
    {
        private List<byte> bytes = new List<byte>();

        internal void Add(bool value)
        {
            bytes.Add(value ? (byte)1 : (byte)0);
        }

        internal void Add(byte value)
        {
            bytes.Add(value);
        }

        internal void Add(ushort value)
        {
            unchecked
            {
                bytes.Add((byte)value);
                bytes.Add((byte)(value >> 8));
            }
        }

        internal void Add(uint value)
        {
            unchecked
            {
                bytes.Add((byte)value);
                bytes.Add((byte)(value >> 8));
                bytes.Add((byte)(value >> 16));
                bytes.Add((byte)(value >> 24));
            }
        }

        internal byte[] GetData()
        {
            return bytes.ToArray();
        }
    }
}
