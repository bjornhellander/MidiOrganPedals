using System;

namespace WpfMidiOrganPedals.Devices
{
    internal class RawMessageExtractor
    {
        private byte[] bytes;
        private int index;

        public RawMessageExtractor(byte[] bytes)
        {
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
    }
}