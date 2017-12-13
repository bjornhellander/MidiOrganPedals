namespace WpfMidiOrganPedals.Devices
{
    internal abstract class RawMessageHandler
    {
        public static byte StartByte => 0xFF;

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
