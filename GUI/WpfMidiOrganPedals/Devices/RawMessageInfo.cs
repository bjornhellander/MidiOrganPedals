namespace WpfMidiOrganPedals.Devices
{
    internal abstract class RawMessageHandler
    {
        public static byte StartByte => 0xFF;
        public static byte DummyMessageId = 0x00;

        protected byte CalcChecksum(byte[] payloadData)
        {
            byte result = 0;

            foreach (var @byte in payloadData)
            {
                result ^= @byte;
            }

            return result;
        }
    }
}
