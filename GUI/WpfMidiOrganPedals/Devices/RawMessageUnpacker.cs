using System;

namespace WpfMidiOrganPedals.Devices
{
    internal class RawMessageUnpacker : RawMessageHandler
    {
        private readonly byte[] data;
        private int dataSize;
        private byte id;
        private byte length;
        private byte checksum;
        private byte[] payloadData;

        public RawMessageUnpacker()
        {
            data = new byte[4 + 255]; // 4 fixed bytes and a variable field specified with an 8-bit length

            Reset();
        }

        public Action<RawMessage> MessageFound { get; internal set; }

        internal void Process(byte[] data)
        {
            var index = 0;
            foreach (var @byte in data)
            {
                Process(@byte);
                index++;
            }
        }

        private void Process(byte @byte)
        {
            switch (dataSize)
            {
                case 0:
                    ProcessStart(@byte);
                    break;
                case 1:
                    ProcessId(@byte);
                    break;
                case 2:
                    ProcessLength(@byte);
                    break;
                case 3:
                    ProcessChecksum(@byte);
                    break;
                default:
                    ProcessPayload(@byte);
                    break;
            }
        }

        private void ProcessStart(byte @byte)
        {
            AddByte(@byte);

            if (@byte != StartByte)
            {
                Abort();
            }
        }

        private void ProcessId(byte @byte)
        {
            AddByte(@byte);

            id = @byte;
        }

        private void ProcessLength(byte @byte)
        {
            AddByte(@byte);

            length = @byte;
            payloadData = new byte[length];
        }

        private void ProcessChecksum(byte @byte)
        {
            AddByte(@byte);

            checksum = @byte;
        }

        private void ProcessPayload(byte @byte)
        {
            // TODO: If length==0 then this code will still consume one byte as payload
            AddByte(@byte);

            var payloadSize = dataSize - 4;
            payloadData[payloadSize-1] = @byte;

            if (payloadSize >= length)
            {
                // Verify checksum
                var expectedChecksum = CalcChecksum(payloadData);
                if (checksum != expectedChecksum)
                {
                    Abort();
                    return;
                }

                // We are done!
                var message = new RawMessage(id, payloadData);
                NotifyMessageFound(message);

                Reset();
            }
        }

        private void AddByte(byte @byte)
        {
            data[dataSize++] = @byte;
        }

        private void Abort()
        {
            // TODO: Log discarded data?

            Reset();
        }

        private void Reset()
        {
            dataSize = 0;
            payloadData = null;
        }

        private void NotifyMessageFound(RawMessage message)
        {
            MessageFound.Invoke(message);
        }
    }
}
