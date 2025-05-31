#include <stdio.h>
#include <string.h>

#include "../include/hash.h"

void test(int num, char *message1, char *test_hash_summ1);
int main() {
  char
      message1[1] = "",
      test_hash_summ1[65] =
          "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855",
      message2[44] = "The quick brown fox jumps over the lazy dog",
      test_hash_summ2[65] =
          "d7a8fbb307d7809469ca9abcb0082e4f8d5651e46d3cdb762d02d0bf37c9e592",
      message3[44] = "The quick brown fox jumps over the lazy cog",
      test_hash_summ3[65] =
          "e4c4d8f3bf76b692de791a173e05321150f7a345b46484fe427f6acc7ecc81be",
      message4[3001] =
          "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean "
          "commodo ligula eget dolor. Aenean massa. Cum sociis natoque "
          "penatibus "
          "et magnis dis parturient montes, nascetur ridiculus mus. Donec quam "
          "felis, ultricies nec, pellentesque eu, pretium quis, sem. Nulla "
          "consequat massa quis enim. Donec pede justo, fringilla vel, aliquet "
          "nec, vulputate eget, arcu. In enim justo, rhoncus ut, imperdiet a, "
          "venenatis vitae, justo. Nullam dictum felis eu pede mollis pretium. "
          "Integer tincidunt. Cras dapibus. Vivamus elementum semper nisi. "
          "Aenean "
          "vulputate eleifend tellus. Aenean leo ligula, porttitor eu, "
          "consequat "
          "vitae, eleifend ac, enim. Aliquam lorem ante, dapibus in, viverra "
          "quis, "
          "feugiat a, tellus. Phasellus viverra nulla ut metus varius laoreet. "
          "Quisque rutrum. Aenean imperdiet. Etiam ultricies nisi vel augue. "
          "Curabitur ullamcorper ultricies nisi. Nam eget dui. Etiam rhoncus. "
          "Maecenas tempus, tellus eget condimentum rhoncus, sem quam semper "
          "libero, sit amet adipiscing sem neque sed ipsum. Nam quam nunc, "
          "blandit "
          "vel, luctus pulvinar, hendrerit id, lorem. Maecenas nec odio et "
          "ante "
          "tincidunt tempus. Donec vitae sapien ut libero venenatis faucibus. "
          "Nullam quis ante. Etiam sit amet orci eget eros faucibus tincidunt. "
          "Duis leo. Sed fringilla mauris sit amet nibh. Donec sodales "
          "sagittis "
          "magna. Sed consequat, leo eget bibendum sodales, augue velit cursus "
          "nunc, quis gravida magna mi a libero. Fusce vulputate eleifend "
          "sapien. "
          "Vestibulum purus quam, scelerisque ut, mollis sed, nonummy id, "
          "metus. "
          "Nullam accumsan lorem in dui. Cras ultricies mi eu turpis hendrerit "
          "fringilla. Vestibulum ante ipsum primis in faucibus orci luctus et "
          "ultrices posuere cubilia Curae; In ac dui quis mi consectetuer "
          "lacinia. "
          "Nam pretium turpis et arcu. Duis arcu tortor, suscipit eget, "
          "imperdiet "
          "nec, imperdiet iaculis, ipsum. Sed aliquam ultrices mauris. Integer "
          "ante arcu, accumsan a, consectetuer eget, posuere ut, mauris. "
          "Praesent "
          "adipiscing. Phasellus ullamcorper ipsum rutrum nunc. Nunc nonummy "
          "metus. Vestibulum volutpat pretium libero. Cras id dui. Aenean ut "
          "eros "
          "et nisl sagittis vestibulum. Nullam nulla eros, ultricies sit amet, "
          "nonummy id, imperdiet feugiat, pede. Sed lectus. Donec mollis "
          "hendrerit "
          "risus. Phasellus nec sem in justo pellentesque facilisis. Etiam "
          "imperdiet imperdiet orci. Nunc nec neque. Phasellus leo dolor, "
          "tempus "
          "non, auctor et, hendrerit quis, nisi. Curabitur ligula sapien, "
          "tincidunt non, euismod vitae, posuere imperdiet, leo. Maecenas "
          "malesuada. Praesent congue erat at massa. Sed cursus turpis vitae "
          "tortor. Donec posuere vulputate arcu. Phasellus accumsan cursus "
          "velit. "
          "Vestibulum ante ipsum primis in faucibus orci luctus et ultrices "
          "posuere cubilia Curae; Sed aliquam, nisi quis porttitor congue, "
          "elit "
          "erat euismod orci, ac placerat dolor lectus quis orci. Phasellus "
          "consectetuer vestibulum elit. Aenean tellus metus, bibendum sed, "
          "posuere ac, mattis non, nunc. Vestibulum fringilla pede sit amet "
          "augue. "
          "In turpis. Pellentesque posuere. Praesent turpis. Aenean posuere, "
          "tor",
      test_hash_summ4[65] =
          "318a4f707a97c98e721b7d240066583d4507dec5ed5a8b8c1ddb2047b98676a7";
  test(1, message1, test_hash_summ1);
  printf("\n");
  test(2, message2, test_hash_summ2);
  printf("\n");
  test(3, message3, test_hash_summ3);
  printf("\n");
  test(4, message4, test_hash_summ4);
  return 0;
}
void test(int num, char *message, char *test_hash_summ) {
  char path[60] = "src/test_message.txt";
  FILE *file = fopen(path, "w");
  fputs(message, file);
  fclose(file);
  char hash_summ[65];
  create_hash(path, hash_summ);
  if (!strcmp(test_hash_summ, hash_summ)) {
    printf("#%d: Test is OK", num);
  } else {
    printf("#%d: Test FAILED!!!", num);
  }
  if (remove(path)) {
    printf("\nCan't remove file");
  }
}
