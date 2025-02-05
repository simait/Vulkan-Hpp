// Copyright(c) 2018, NVIDIA CORPORATION. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// VulkanHpp Samples : ArrayProxyNoTemporaries
//                     Compile test on using vk::ArrayProxyNoTemporaries

#if defined( _MSC_VER )
// no need to ignore any warnings with MSVC
#elif defined( __GNUC__ )
#  if ( 9 <= __GNUC__ )
#    pragma GCC diagnostic ignored "-Winit-list-lifetime"
#  endif
#else
// unknow compiler... just ignore the warnings for yourselves ;)
#endif

#include "vulkan/vulkan.hpp"

#include <iostream>

void fct( vk::ArrayProxyNoTemporaries<int> /*ap*/ ) {}

void fctc( vk::ArrayProxyNoTemporaries<const int> /*ap*/ ) {}

int getInt()
{
  return 1;
}

std::array<int, 2> getArray()
{
  return { 1, 2 };
}

std::array<int, 2> const getConstArray()
{
  return { 1, 2 };
}

std::vector<int> getVector()
{
  return { 1, 2 };
}

std::vector<int> const getConstVector()
{
  return { 1, 2 };
}

std::initializer_list<int> getInitializerList()
{
  return { 1, 2 };
}

std::initializer_list<int> const getConstInitializerList()
{
  return { 1, 2 };
}

int main( int /*argc*/, char ** /*argv*/ )
{
  try
  {
    // to prevent a warning on unreferenced function vk::getDispatchLoaderStatic, use just one arbitrary vk-function
    vk::enumerateInstanceVersion();

    // nullptr_t
    fct( nullptr );
    fctc( nullptr );

    vk::ArrayProxyNoTemporaries<int> ap0 = nullptr;
    assert( ap0.size() == 0 );

    // Type
    // fct(2);   // not supported: attempting to reference a deleted function: ArrayProxyNoTemporaries<int>(int &&)
    // fctc(1);  // not supported: attempting to reference a deleted function: ArrayProxyNoTemporaries<T,0>(int &&)

    // getInt()
    // fct( getInt() );    // not supported: attempting to reference a deleted function: ArrayProxyNoTemporaries<int>(int &&)
    // fctc( getInt() );   // not supported: attempting to reference a deleted function: ArrayProxyNoTemporaries<T,0>(int &&)

    int i0 = 1;
    fct( i0 );
    fctc( i0 );

    const int i1 = 2;
    // fct(i1);   // not supported: ArrayProxyNoTemporaries<const int&>(const int &)
    fctc( i1 );

    // count, T *
    int * i0p = &i0;
    fct( { 1, i0p } );
    fctc( { 1, i0p } );

    // count, T const*
    int const * i1p = &i1;
    // fct({ 1, i1p });   // not supported: cannot convert argument 1 from 'initializer list' to 'vk::ArrayProxyNoTemporaries<int>'
    fctc( { 1, i1p } );

    // std::array<T,N>
    std::array<int, 2> sa0 = { 0, 1 };
    fct( sa0 );
    fctc( sa0 );

    // std::array<const T,N>
    std::array<const int, 2> sa1 = { 0, 1 };
    // fct(sa1); // not supported: attempting to reference a deleted function: ArrayProxyNoTemporaries<std::array<const int,2>&>(V)
    fctc( sa1 );

    // std::array<T,N> const
    std::array<int, 2> const sa2 = { 1, 2 };
    // fct(sa2);    // not supported: attempting to reference a deleted function: ArrayProxyNoTemporaries<const std::array<int,2>&>(V)
    fctc( sa2 );

    // std::array<const T,N> const
    std::array<const int, 2> const sa3 = { 1, 2 };
    // fct(sa3); // not supported: attempting to reference a deleted function: ArrayProxyNoTemporaries<const std::array<const int,2>&>(V)
    fctc( sa3 );

    // getArray
    // fct( getConstArray() );    // not supported: attempting to reference a deleted function: ArrayProxyNoTemporaries<const std::array<int,2>>(V &&)
    // fctc( getConstArray() );   // not supported: attempting to reference a deleted function: ArrayProxyNoTemporaries<const std::array<int,2>>(V &&)
    // fct( getArray() );         // not supported: attempting to reference a deleted function: ArrayProxyNoTemporaries<std::array<int,2>>(V &&)
    // fctc( getArray() );        // not supported: attempting to reference a deleted function: ArrayProxyNoTemporaries<std::array<int,2>>(V &&)

    // from std::array constructors
    vk::ArrayProxyNoTemporaries<int> ap2 = sa0;
    assert( ap2.size() == 2 );
    // vk::ArrayProxyNoTemporaries<int> ap3 = sa1;  // not supported: attempting to reference a deleted function: ArrayProxyNoTemporaries<std::array<const
    // int,2>&>(V) vk::ArrayProxyNoTemporaries<int> ap4 = sa2;  // not supported: attempting to reference a deleted function: ArrayProxyNoTemporaries<const
    // std::array<int,2>&>(V) vk::ArrayProxyNoTemporaries<int> ap5 = sa3;  // not supported: attempting to reference a deleted function:
    // ArrayProxyNoTemporaries<const std::array<const int,2>&>(V)

    vk::ArrayProxyNoTemporaries<const int> ap6 = sa0;
    assert( ap6.size() == 2 );
    vk::ArrayProxyNoTemporaries<const int> ap7 = sa1;
    assert( ap7.size() == 2 );
    vk::ArrayProxyNoTemporaries<const int> ap8 = sa2;
    assert( ap8.size() == 2 );
    vk::ArrayProxyNoTemporaries<const int> ap9 = sa3;
    assert( ap9.size() == 2 );

    // std::vector<T>
    std::vector<int> sv0 = { 0, 1 };
    fct( sv0 );
    fctc( sv0 );

    // std::vector<T> const
    std::vector<int> const sv1 = { 0, 1 };
    // fct(sv1); // not supported:  attempting to reference a deleted function: ArrayProxyNoTemporaries<const std::vector<int,std::allocator<int>>&>(V)
    fctc( sv1 );

    vk::ArrayProxyNoTemporaries<int> ap10 = sv0;
    assert( ap10.size() == 2 );
    // vk::ArrayProxyNoTemporaries<int> ap11 = sv1;  // not supported: attempting to reference a deleted function: ArrayProxyNoTemporaries<const
    // std::vector<int,std::allocator<int>>&>(V)

    // getVector
    // fct( getConstVector() );    // not supported: attempting to reference a deleted function: ArrayProxyNoTemporaries<const
    // std::vector<int,std::allocator<int>>>(V &&) fctc( getConstVector() );   // not supported: attempting to reference a deleted function:
    // ArrayProxyNoTemporaries<const std::vector<int,std::allocator<int>>>(V &&) fct( getVector() );         // not supported: attempting to reference a deleted
    // function: ArrayProxyNoTemporaries<std::vector<int,std::allocator<int>>>(V &&) fctc( getVector() );        // not supported: attempting to reference a
    // deleted function: ArrayProxyNoTemporaries<std::vector<int,std::allocator<int>>>(V &&)

    vk::ArrayProxyNoTemporaries<const int> ap12 = sv0;
    assert( ap12.size() == 2 );
    vk::ArrayProxyNoTemporaries<const int> ap13 = sv1;
    assert( ap13.size() == 2 );

    // std::initializer_list
    fct( {} );
    fctc( {} );

    // fct({ 0, 1 });    // not supported: cannot convert argument 1 from 'initializer list' to 'vk::ArrayProxyNoTemporaries<int>'
    // fctc({ 0, 1 });   // not supported: cannot convert argument 1 from 'initializer list' to 'vk::ArrayProxyNoTemporaries<const int32_t>'

    // int a = 0;
    // int b = 1;
    // fct({ a, b });    // not supported: cannot convert argument 1 from 'initializer list' to 'vk::ArrayProxyNoTemporaries<int>'
    // fctc({ a,b });    // not supported: cannot convert argument 1 from 'initializer list' to 'vk::ArrayProxyNoTemporaries<const int32_t>'

    auto il0 = { 0, 1 };  // -> std::initializer_list<int>
    // fct(il0);  // not supported: cannot convert from 'const int *' to 'int *'
    fctc( il0 );

    std::initializer_list<int> il1 = { 0, 1 };
    // fct(il1);  // not supported: cannot convert from 'const int *' to 'int *'
    fctc( il1 );

    std::initializer_list<const int> il2 = { 0, 1 };
    // fct(il2);  // not supported: attempting to reference a deleted function : ArrayProxyNoTemporaries<std::initializer_list<T>&>(V)
    fctc( il2 );

    std::initializer_list<int> const il3 = { 0, 1 };
    // fct(il3);  // not supported: cannot convert from 'const int *' to 'int *'
    fctc( il3 );

    std::initializer_list<const int> const il4 = { 0, 1 };
    // fct(il4);  // not supported: attempting to reference a deleted function: ArrayProxyNoTemporaries<const std::initializer_list<T>&>(V)
    fctc( il4 );

    // getInitializerList
    // fct( getConstInitializerList() );     // not supported: attempting to reference a deleted function: ArrayProxyNoTemporaries(const
    // std::initializer_list<int> &&) fctc( getConstInitializerList() );    // not supported: attempting to reference a deleted function:
    // ArrayProxyNoTemporaries<T,0>(const std::initializer_list<int> &&) fct( getInitializerList() );          // not supported: attempting to reference a
    // deleted function: ArrayProxyNoTemporaries(std::initializer_list<int> &&) fctc( getInitializerList() );         // not supported: attempting to reference
    // a deleted function: ArrayProxyNoTemporaries<T,0>(std::initializer_list<int> &&)

    // vk::ArrayProxyNoTemporaries<int> ap14 = il1;   // not supported: cannot convert from 'const int *' to 'int *'
    // vk::ArrayProxyNoTemporaries<int> ap15 = il2;   // not supported: attempting to reference a deleted function:
    // ArrayProxyNoTemporaries<std::initializer_list<T>&>(V) vk::ArrayProxyNoTemporaries<int> ap16 = il3;   // not supported: cannot convert from 'const int *'
    // to 'int *' vk::ArrayProxyNoTemporaries<int> ap17 = il4;   // not supported: attempting to reference a deleted function: ArrayProxyNoTemporaries<const
    // std::initializer_list<T>&>(V)

    vk::ArrayProxyNoTemporaries<const int> ap18 = il1;
    assert( ap18.size() == 2 );
    vk::ArrayProxyNoTemporaries<const int> ap19 = il2;
    assert( ap19.size() == 2 );
    vk::ArrayProxyNoTemporaries<const int> ap20 = il3;
    assert( ap20.size() == 2 );
    vk::ArrayProxyNoTemporaries<const int> ap21 = il4;
    assert( ap21.size() == 2 );
  }
  catch ( vk::SystemError const & err )
  {
    std::cout << "vk::SystemError: " << err.what() << std::endl;
    exit( -1 );
  }
  catch ( ... )
  {
    std::cout << "unknown error\n";
    exit( -1 );
  }

  return 0;
}
