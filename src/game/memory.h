
#include "primitives.h"

namespace gameboy
{
    class memory 
    {
        private:
            byte cartridge[32 * KB];

        public:
            byte get_in_addr(address add);

            void set_in_addr(address add, byte byte_to_insert);
    };
}