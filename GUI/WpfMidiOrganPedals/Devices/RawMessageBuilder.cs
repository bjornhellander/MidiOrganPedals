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

        internal void Add(byte[] value, int size)
        {
            if (value.Length > size)
            {
                throw new ArgumentException("Array too long", nameof(value));
            }

            for (var i = 0; i < size; i++)
            {
                var temp = i < value.Length ? value[i] : (byte)0;
                bytes.Add(temp);
            }
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

        internal void Add(string text, int length)
        {
            for (var i = 0; i < length; i++)
            {
                var @char = i < text.Length ? text[i] : (char)0;
                bytes.Add((byte)@char);
            }
        }

        internal byte[] GetData()
        {
            return bytes.ToArray();
        }
    }
}
