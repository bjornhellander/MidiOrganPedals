using System;

namespace WpfMidiOrganPedals.Devices
{
    internal class RawMessageExtractor
    {
        private byte[] bytes;
        private int index;

        public RawMessageExtractor(byte[] bytes)
        {
            if (bytes == null)
            {
                throw new ArgumentNullException(nameof(bytes));
            }

            this.bytes = bytes;
            this.index = 0;
        }

        internal void Get(ref bool value)
        {
            var temp = bytes[index++];
            value = temp != 0 ? true : false;
        }

        internal void Get(ref byte value)
        {
            var temp = bytes[index++];
            value = temp;
        }

        internal void Get(ref byte[] value, int size)
        {
            value = new byte[size];
            for (var i = 0; i < size; i++)
            {
                value[i] = bytes[index++];
            }
        }

        internal void Get(ref ushort value)
        {
            uint temp1 = bytes[index++];
            uint temp2 = bytes[index++];
            uint temp = (temp2 << 8) + temp1;
            value = (ushort)temp;
        }

        internal void Get(ref uint value)
        {
            uint temp1 = bytes[index++];
            uint temp2 = bytes[index++];
            uint temp3 = bytes[index++];
            uint temp4 = bytes[index++];
            value = (temp4 << 24) + (temp3 << 16) + (temp2 << 8) + temp1;
        }

        internal void Get(ref string text, int length)
        {
            var result = "";
            var done = false;
            for (var i = 0; i < length; i++)
            {
                var temp = bytes[index++];
                done = done || temp == 0;
                if (!done)
                {
                    result += (char)temp;
                }
            }
            
            text = result;
        }

        internal void Finish()
        {
            if (index != bytes.Length)
            {
                throw new ArgumentException("Incorrect message length");
            }
        }
    }
}
